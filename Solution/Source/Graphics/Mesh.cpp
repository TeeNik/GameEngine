#include "Graphics/Mesh.hpp"
#include "Graphics/Renderer.hpp"
#include "Graphics/Texture.hpp"
#include "Graphics/VertexArray.hpp"
#include "Math/Math.h"
#include "Engine/Engine.hpp"
#include "Graphics/Shader.hpp"

#include "Utils/Utils.hpp"
#include "glew.h"
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <cassert>
#include <iostream>
#include <fstream>

Mesh::Mesh(const std::vector<Vertex>& v, const std::vector<unsigned int>& ind) :
	radius(0.0f), 
	specPower(100.0f),
	box(Vector3::Infinity, Vector3::NegInfinity)
{
	vertices = v;
	indices = ind;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
		&indices[0], GL_STATIC_DRAW);

	// vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	// vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));

	glBindVertexArray(0);

	CalculateBox(v);
}

Mesh::Mesh(const aiMesh* mesh, const aiScene* scene) :
	radius(0.0f),
	specPower(100.0f),
	box(Vector3::Infinity, Vector3::NegInfinity)
{

}

Mesh::Mesh() : 
radius(0.0f),
specPower(100.0f),
box(Vector3::Infinity, Vector3::NegInfinity)
{

}

Mesh::~Mesh()
{
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO);
}

/*
void Mesh::SetTexture(Renderer* renderer, const std::string& path)
{
	textures.emplace_back(renderer->GetTexture(path));
}
*/

void Mesh::SetTexture(Texture* t)
{
	textures.emplace_back(t);
}

Texture* Mesh::GetTexture(size_t index)
{
	if (index < textures.size())
	{
		return textures[index];
	}
	else
	{
		return nullptr;
	}
}

void Mesh::Draw(Shader * shader)
{
	std::vector<aiMatrix4x4> transforms;
	BoneTransform((double)SDL_GetTicks() / 1000.0f, transforms);
	//BoneTransform(0, transforms);
	//readFromFile(transforms);
	for (int i = 0; i < transforms.size(); i++) // move all matrices for actual model position to shader
	{
		//printMatr(transforms[i]);
		std::string name = "uBones[" + std::to_string(i) + "]";
		shader->SetMatrixUniform(name.c_str(), toMat4(transforms[i]));
		//GLuint loc = glGetUniformLocation(shader->shaderProgram, name.c_str());
		//glUniformMatrix4fv(loc, 1, GL_TRUE, (const GLfloat*)& transforms[i]);
		aiMatrix4x4 identity;
		//glUniformMatrix4fv(loc, 1, GL_TRUE, (const GLfloat*)& identity);
	}

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);
}

void Mesh::LoadMesh(const std::string& path)
{
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		printf("ERROR::ASSIMP %s\n", importer.GetErrorString());
		return;
	}
	if (scene->mNumMeshes > 1)
	{
		printf("ERROR NumMeshes > 1\n");
		return;
	}
	ProcessMesh(scene->mMeshes[0], scene);
}

void Mesh::ProcessNode(aiNode* node, const aiScene* scene)
{
	for (int i = 0; i < node->mNumMeshes; ++i)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		ProcessMesh(mesh, scene);
	}

	for (int i = 0; i < node->mNumChildren; ++i)
	{
		ProcessNode(node->mChildren[i], scene);
	}
}

void Mesh::ProcessMesh(aiMesh* m, const aiScene* scene)
{

	m_global_inverse_transform = scene->mRootNode->mTransformation;
	m_global_inverse_transform.Inverse();
 
	const int vectorSize = 3;
	//std::vector<Vertex> vertices;
	for (int i = 0; i < m->mNumVertices; ++i)
	{
		Vertex vertex;

		auto pos = m->mVertices[i];
		vertex.position.x = pos.x;
		vertex.position.y = pos.y;
		vertex.position.z = pos.z;

		if (m->HasNormals())
		{
			auto normal = m->mNormals[i];
			vertex.normal.x = normal.x;
			vertex.normal.y = normal.y;
			vertex.normal.z = normal.z;
		}

		if (m->mTextureCoords[0])
		{
			auto tex = m->mTextureCoords[0][i];
			vertex.texCoords.x = tex.x;
			vertex.texCoords.y = tex.y;
		}
		else {
			vertex.texCoords = Vector2::Zero;
		}

		vertices.push_back(vertex);
	}

	//std::vector<unsigned int> indeces;
	for (int i = 0; i < m->mNumFaces; ++i)
	{
		auto face = m->mFaces[i];
		for (int j = 0; j < face.mNumIndices; ++j)
		{
			indices.emplace_back(face.mIndices[j]);
		}
	}

	//Mesh* mesh = new Mesh(vertices, indeces);
	Bones.resize(m->mNumVertices);
	for (int i = 0; i < m->mNumBones; ++i)
	{
		int boneIndex = 0;
		std::string boneName(m->mBones[i]->mName.data);

		if (m_BoneMapping.find(boneName) == m_BoneMapping.end())
		{
			boneIndex = m_NumBones;
			m_NumBones++;
			BoneMatrix bi;
			m_BoneInfo.push_back(bi);
			m_BoneInfo[boneIndex].offset_matrix = m->mBones[i]->mOffsetMatrix;
			m_BoneMapping[boneName] = boneIndex;
		}
		else
		{
			boneIndex = m_BoneMapping[boneName];
		}

		for (int j = 0; j < m->mBones[i]->mNumWeights; ++j)
		{
			int vertexID = m->mBones[i]->mWeights[j].mVertexId;
			float weight = m->mBones[i]->mWeights[j].mWeight;
			Bones[vertexID].addBoneData(boneIndex, weight);
		}
	}

	_scene = scene;
	if (scene->mTextures > 0) {
		SetTexture(engine->GetRenderer()->GetTexture(scene, m));
	}
	SetupMesh();
}

void Mesh::SetupMesh()
{
	/*
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
		&indices[0], GL_STATIC_DRAW);

	//bones data
	//glGenBuffers(1, &VBO_bones);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO_bones);
	//glBufferData(GL_ARRAY_BUFFER, Bones.size() * sizeof(Bones[0]), &Bones[0], GL_STATIC_DRAW);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	// vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	// vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
	//bones
	//glBindBuffer(GL_ARRAY_BUFFER, VBO_bones);
	//glEnableVertexAttribArray(3);
	//glVertexAttribIPointer(3, 4, GL_INT, sizeof(VertexBoneData), (GLvoid*)0); // for INT Ipointer
	//glEnableVertexAttribArray(4);
	//glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(VertexBoneData), (GLvoid*)offsetof(VertexBoneData, Weights));
	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
	*/

	//vertices data
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), &vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//bones data
	glGenBuffers(1, &VBO_bones);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_bones);
	glBufferData(GL_ARRAY_BUFFER, Bones.size() * sizeof(Bones[0]), &Bones[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//numbers for sequence indices
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// create VAO and binding data from buffers to shaders
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//vertex position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
	glEnableVertexAttribArray(1); // offsetof(Vertex, normal) = returns the byte offset of that variable from the start of the struct
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoords));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//bones
	glBindBuffer(GL_ARRAY_BUFFER, VBO_bones);
	glEnableVertexAttribArray(3);
	glVertexAttribIPointer(3, 4, GL_INT, sizeof(VertexBoneData), (GLvoid*)0); // for INT Ipointer
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(VertexBoneData), (GLvoid*)offsetof(VertexBoneData, Weights));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBindVertexArray(0);

	CalculateBox(vertices);
}

void Mesh::BoneTransform(float timeInSeconds, std::vector<aiMatrix4x4>& transforms)
{
	aiMatrix4x4 identity;
	float TicksPerSecond = _scene->mAnimations[0]->mTicksPerSecond != 0 ? _scene->mAnimations[0]->mTicksPerSecond : 25.0f;
	float TimeInTicks = timeInSeconds * TicksPerSecond;
	float AnimationTime = fmod(TimeInTicks, _scene->mAnimations[0]->mDuration);

	ReadNodeHierarchy(AnimationTime, _scene->mRootNode, identity);

	transforms.resize(m_NumBones);
	for (int i = 0; i < m_NumBones; i++) {
		transforms[i] = m_BoneInfo[i].final_world_transform;
	}
}

void Mesh::ReadNodeHierarchy(float AnimationTime, const aiNode* pNode, const aiMatrix4x4 ParentTransform)
{
	std::string NodeName(pNode->mName.data);

	const aiAnimation* pAnimation = _scene->mAnimations[0];

	aiMatrix4x4 NodeTransformation(pNode->mTransformation);

	const aiNodeAnim* pNodeAnim = FindNodeAnim(pAnimation, NodeName);

	if (pNodeAnim) 
	{
		aiVector3D scaling_vector = CalcInterpolatedScaling(AnimationTime, pNodeAnim);
		aiMatrix4x4 scaling_matr;
		aiMatrix4x4::Scaling(scaling_vector, scaling_matr);

		//rotation
		//aiQuaternion rotate_quat = node_anim->mRotationKeys[2].mValue;
		aiQuaternion rotate_quat = CalcInterpolatedRotation(AnimationTime, pNodeAnim);
		aiMatrix4x4 rotate_matr = aiMatrix4x4(rotate_quat.GetMatrix());

		//translation
		//aiVector3D translate_vector = node_anim->mPositionKeys[2].mValue;
		aiVector3D translate_vector = CalcInterpolatedPosition(AnimationTime, pNodeAnim);
		aiMatrix4x4 translate_matr;
		aiMatrix4x4::Translation(translate_vector, translate_matr);
		// Combine the above transformations

		NodeTransformation = translate_matr * rotate_matr * scaling_matr;
	}

	aiMatrix4x4 GlobalTransformation = ParentTransform * NodeTransformation;

	if (m_BoneMapping.find(NodeName) != m_BoneMapping.end()) {
		int BoneIndex = m_BoneMapping[NodeName];
		m_BoneInfo[BoneIndex].final_world_transform = m_global_inverse_transform * GlobalTransformation *
			m_BoneInfo[BoneIndex].offset_matrix;
	}

	for (int i = 0; i < pNode->mNumChildren; i++) {
		ReadNodeHierarchy(AnimationTime, pNode->mChildren[i], GlobalTransformation);
	}
}

const aiNodeAnim* Mesh::FindNodeAnim(const aiAnimation* animation, const std::string p_node_name)
{
	for (int i = 0; i < animation->mNumChannels; i++)
	{
		const aiNodeAnim* node_anim = animation->mChannels[i];
		if (std::string(node_anim->mNodeName.data) == p_node_name)
		{
			return node_anim;
		}
	}
	return nullptr;
}

int Mesh::FindPosition(float p_animation_time, const aiNodeAnim* p_node_anim)
{
	for (int i = 0; i < p_node_anim->mNumPositionKeys - 1; i++)
	{
		if (p_animation_time < (float)p_node_anim->mPositionKeys[i + 1].mTime)
		{
			return i; 
		}
	}
	assert(0);
	return 0;
}

int Mesh::FindRotation(float p_animation_time, const aiNodeAnim* p_node_anim)
{
	for (int i = 0; i < p_node_anim->mNumRotationKeys - 1; i++)
	{
		if (p_animation_time < (float)p_node_anim->mRotationKeys[i + 1].mTime)
		{
			return i;
		}
	}
	assert(0);
	return 0;
}

int Mesh::FindScaling(float p_animation_time, const aiNodeAnim* p_node_anim)
{
	for (int i = 0; i < p_node_anim->mNumScalingKeys - 1; i++)
	{
		if (p_animation_time < (float)p_node_anim->mScalingKeys[i + 1].mTime)
		{
			return i;
		}
	}
	assert(0);
	return 0;
}

aiVector3D Mesh::CalcInterpolatedPosition(float p_animation_time, const aiNodeAnim* p_node_anim)
{
	if (p_node_anim->mNumPositionKeys == 1)
	{
		return p_node_anim->mPositionKeys[0].mValue;
	}

	int position_index = FindPosition(p_animation_time, p_node_anim);
	int next_position_index = position_index + 1;
	assert(next_position_index < p_node_anim->mNumPositionKeys);
	float delta_time = (float)(p_node_anim->mPositionKeys[next_position_index].mTime - p_node_anim->mPositionKeys[position_index].mTime);
	float factor = (p_animation_time - (float)p_node_anim->mPositionKeys[position_index].mTime) / delta_time;
	assert(factor >= 0.0f && factor <= 1.0f);
	aiVector3D start = p_node_anim->mPositionKeys[position_index].mValue;
	aiVector3D end = p_node_anim->mPositionKeys[next_position_index].mValue;
	aiVector3D delta = end - start;

	return start + factor * delta;
}

aiQuaternion Mesh::CalcInterpolatedRotation(float p_animation_time, const aiNodeAnim* p_node_anim)
{
	if (p_node_anim->mNumRotationKeys == 1)
	{
		return p_node_anim->mRotationKeys[0].mValue;
	}

	int rotation_index = FindRotation(p_animation_time, p_node_anim);
	int next_rotation_index = rotation_index + 1;
	assert(next_rotation_index < p_node_anim->mNumRotationKeys);
	float delta_time = (float)(p_node_anim->mRotationKeys[next_rotation_index].mTime - p_node_anim->mRotationKeys[rotation_index].mTime);
	float factor = (p_animation_time - (float)p_node_anim->mRotationKeys[rotation_index].mTime) / delta_time;

	assert(factor >= 0.0f && factor <= 1.0f);
	aiQuaternion start_quat = p_node_anim->mRotationKeys[rotation_index].mValue;
	aiQuaternion end_quat = p_node_anim->mRotationKeys[next_rotation_index].mValue;

	return nlerp(start_quat, end_quat, factor);
}

aiVector3D Mesh::CalcInterpolatedScaling(float p_animation_time, const aiNodeAnim* p_node_anim)
{
	if (p_node_anim->mNumScalingKeys == 1)
	{
		return p_node_anim->mScalingKeys[0].mValue;
	}

	int scaling_index = FindScaling(p_animation_time, p_node_anim);
	int next_scaling_index = scaling_index + 1;
	assert(next_scaling_index < p_node_anim->mNumScalingKeys);
	float delta_time = (float)(p_node_anim->mScalingKeys[next_scaling_index].mTime - p_node_anim->mScalingKeys[scaling_index].mTime);
	float  factor = (p_animation_time - (float)p_node_anim->mScalingKeys[scaling_index].mTime) / delta_time;
	assert(factor >= 0.0f && factor <= 1.0f);
	aiVector3D start = p_node_anim->mScalingKeys[scaling_index].mValue;
	aiVector3D end = p_node_anim->mScalingKeys[next_scaling_index].mValue;
	aiVector3D delta = end - start;

	return start + factor * delta;
}

aiQuaternion Mesh::nlerp(aiQuaternion a, aiQuaternion b, float blend)
{
	a.Normalize();
	b.Normalize();

	aiQuaternion result;
	float dot_product = a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	float one_minus_blend = 1.0f - blend;

	if (dot_product < 0.0f)
	{
		result.x = a.x * one_minus_blend + blend * -b.x;
		result.y = a.y * one_minus_blend + blend * -b.y;
		result.z = a.z * one_minus_blend + blend * -b.z;
		result.w = a.w * one_minus_blend + blend * -b.w;
	}
	else
	{
		result.x = a.x * one_minus_blend + blend * b.x;
		result.y = a.y * one_minus_blend + blend * b.y;
		result.z = a.z * one_minus_blend + blend * b.z;
		result.w = a.w * one_minus_blend + blend * b.w;
	}

	return result.Normalize();
}

Matrix4 Mesh::toMat4(aiMatrix4x4 ai_matr)
{
	Matrix4 mat4;
	mat4.mat[0][0] = ai_matr.a1; mat4.mat[0][1] = ai_matr.b1; mat4.mat[0][2] = ai_matr.c1; mat4.mat[0][3] = ai_matr.d1;
	mat4.mat[1][0] = ai_matr.a2; mat4.mat[1][1] = ai_matr.b2; mat4.mat[1][2] = ai_matr.c2; mat4.mat[1][3] = ai_matr.d2;
	mat4.mat[2][0] = ai_matr.a3; mat4.mat[2][1] = ai_matr.b3; mat4.mat[2][2] = ai_matr.c3; mat4.mat[2][3] = ai_matr.d3;
	mat4.mat[3][0] = ai_matr.a4; mat4.mat[3][1] = ai_matr.b4; mat4.mat[3][2] = ai_matr.c4; mat4.mat[3][3] = ai_matr.d4;
	return mat4;
}

void Mesh::printMatr(aiMatrix4x4 ai_matr)
{
	Matrix4 mat4;
	mat4.mat[0][1] = 0;
	std::cout << " " << ai_matr.a1 << "		 " << ai_matr.b1 << "		 " << ai_matr.c1 << "		 " << ai_matr.d1 << std::endl;
	std::cout << " " << ai_matr.a2 << "		 " << ai_matr.b2 << "		 " << ai_matr.c2 << "		 " << ai_matr.d2 << std::endl;
	std::cout << " " << ai_matr.a3 << "		 " << ai_matr.b3 << "		 " << ai_matr.c3 << "		 " << ai_matr.d3 << std::endl;
	std::cout << " " << ai_matr.a4 << "		 " << ai_matr.b4 << "		 " << ai_matr.c4 << "		 " << ai_matr.d4 << std::endl;
	std::cout << std::endl;
}

void Mesh::readFromFile(std::vector<aiMatrix4x4>& transforms)
{
	std::ifstream myfile;
	myfile.open("tranform.txt");
	for (aiMatrix4x4& ai_matr : transforms)
	{
		myfile >> ai_matr.a1 >> ai_matr.b1 >> ai_matr.c1 >> ai_matr.d1;
		myfile >> ai_matr.a2 >> ai_matr.b2 >> ai_matr.c2 >> ai_matr.d2;
		myfile >> ai_matr.a3 >> ai_matr.b3 >> ai_matr.c3 >> ai_matr.d3;
		myfile >> ai_matr.a4 >> ai_matr.b4 >> ai_matr.c4 >> ai_matr.d4;
	}
	myfile.close();
}

void Mesh::CalculateBox(const std::vector<Vertex>& vertices)
{
	for (auto& v : vertices)
	{
		radius = Math::Max(radius, v.position.LengthSq());
		box.UpdateMinMax(v.position);
	}
	radius = Math::Sqrt(radius);
}
