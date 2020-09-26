#include "Graphics/SkeletalMesh.hpp"
#include "assimp/scene.h"
#include <cassert>
#include <SDL.h>

SkeletalMesh::SkeletalMesh(const std::vector<Vertex>& v, const std::vector<unsigned int>& ind, const aiScene* s) : Mesh(v, ind)
{
	scene = s;
	printf("%d\n", scene->mNumAnimations);
}

void SkeletalMesh::Draw(Shader* shader)
{
	std::vector<aiMatrix4x4> transforms;
	BoneTransform((double)SDL_GetTicks() / 1000.0f, transforms);
	for (int i = 0; i < transforms.size(); i++) // move all matrices for actual model position to shader
	{
		glUniformMatrix4fv(boneLocation[i], 1, GL_TRUE, (const GLfloat*)& transforms[i]);
	}

	Mesh::Draw(shader);
}

void SkeletalMesh::LoadAnimation(const aiScene* scene, aiMesh* m)
{
	globalInverseTransform = scene->mRootNode->mTransformation;
	globalInverseTransform.Inverse();

	const float sceneTicks = scene->mAnimations[0]->mTicksPerSecond;
	ticksPerSecond = sceneTicks != 0.0f ? sceneTicks : 25.0f;

	std::vector<VertexBoneData> bonesIdWeightsForEachVertex;
	bonesIdWeightsForEachVertex.resize(m->mNumVertices);

	/*
	printf("scene->HasAnimations() 1: %d\n", scene->HasAnimations());
	printf("scene->mNumMeshes 1: %d\n", scene->mNumMeshes);
	printf("scene->mAnimations[0]->mNumChannels 1: %d\n", scene->mAnimations[0]->mNumChannels);
	printf("scene->mAnimations[0]->mDuration 1: %f\n", scene->mAnimations[0]->mDuration);
	printf("scene->mAnimations[0]->mTicksPerSecond 1: %f\n", scene->mAnimations[0]->mTicksPerSecond);
	*/

	for (int i = 0; i < m->mNumBones; i++)
	{
		int boneIndex = 0;
		std::string bone_name(m->mBones[i]->mName.data);

		//printf(m->mBones[i]->mName.data);

		if (boneMapping.find(bone_name) == boneMapping.end())
		{
			boneIndex = numOfBones;
			numOfBones++;
			BoneMatrix bi;
			boneMatrices.push_back(bi);
			boneMatrices[boneIndex].offset_matrix = m->mBones[i]->mOffsetMatrix;
			boneMapping[bone_name] = boneIndex;
		}
		else
		{
			boneIndex = boneMapping[bone_name];
		}

		for (int j = 0; j < m->mBones[i]->mNumWeights; j++)
		{
			const int vertex_id = m->mBones[i]->mWeights[j].mVertexId;
			const float weight = m->mBones[i]->mWeights[j].mWeight;
			bonesIdWeightsForEachVertex[vertex_id].addBoneData(boneIndex, weight);
		}
	}

	printf("LoadAnimation");
}

aiQuaternion SkeletalMesh::NLerp(aiQuaternion a, aiQuaternion b, float blend)
{
	a.Normalize();
	b.Normalize();

	aiQuaternion result;
	float dotProduct = a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	float oneMinusBlend = 1.0f - blend;

	if (dotProduct < 0.0f)
	{
		result.x = a.x * oneMinusBlend + blend * -b.x;
		result.y = a.y * oneMinusBlend + blend * -b.y;
		result.z = a.z * oneMinusBlend + blend * -b.z;
		result.w = a.w * oneMinusBlend + blend * -b.w;
	}
	else
	{
		result.x = a.x * oneMinusBlend + blend * b.x;
		result.y = a.y * oneMinusBlend + blend * b.y;
		result.z = a.z * oneMinusBlend + blend * b.z;
		result.w = a.w * oneMinusBlend + blend * b.w;
	}

	return result.Normalize();
}

int SkeletalMesh::FindPosition(float animationTime, const aiNodeAnim* nodeAnim)
{
	for (int i = 0; i < nodeAnim->mNumPositionKeys - 1; i++)
	{
		if (animationTime < static_cast<float>(nodeAnim->mPositionKeys[i + 1].mTime))
		{
			return i;
		}
	}
	return 0;
}

int SkeletalMesh::FindRotation(float animationTime, const aiNodeAnim* nodeAnim)
{
	for (int i = 0; i < nodeAnim->mNumRotationKeys - 1; i++)
	{
		if (animationTime < static_cast<float>(nodeAnim->mRotationKeys[i + 1].mTime))
		{
			return i;
		}
	}
	return 0;
}

int SkeletalMesh::FindScaling(float animationTime, const aiNodeAnim* nodeAnim)
{
	for (int i = 0; i < nodeAnim->mNumScalingKeys - 1; i++)
	{
		if (animationTime < static_cast<float>(nodeAnim->mScalingKeys[i + 1].mTime))
		{
			return i;
		}
	}
	return 0;
}

const aiNodeAnim* SkeletalMesh::FindNodeAnim(const aiAnimation* animation, const std::string nodeName)
{
	for (int i = 0; i < animation->mNumChannels; i++)
	{
		const aiNodeAnim* nodeAnim = animation->mChannels[i];
		if (std::string(nodeAnim->mNodeName.data) == nodeName)
		{
			return nodeAnim;
		}
	}
	return nullptr;
}

aiVector3D SkeletalMesh::CalcInterpolatedPosition(float animationTime, const aiNodeAnim* nodeAnim)
{
	if (nodeAnim->mNumPositionKeys == 1)
	{
		return nodeAnim->mPositionKeys[0].mValue;
	}

	int positionIndex = FindPosition(animationTime, nodeAnim);
	int nextPositionIndex = positionIndex + 1;
	assert(nextPositionIndex < nodeAnim->mNumPositionKeys);
	
	float deltaTime = (float)(nodeAnim->mPositionKeys[nextPositionIndex].mTime - nodeAnim->mPositionKeys[positionIndex].mTime);
	
	float factor = (animationTime - (float)nodeAnim->mPositionKeys[positionIndex].mTime) / deltaTime;
	assert(factor >= 0.0f && factor <= 1.0f);
	aiVector3D start = nodeAnim->mPositionKeys[positionIndex].mValue;
	aiVector3D end = nodeAnim->mPositionKeys[nextPositionIndex].mValue;
	aiVector3D delta = end - start;

	return start + factor * delta;
}

aiQuaternion SkeletalMesh::CalcInterpolatedRotation(float animationTime, const aiNodeAnim* nodeAnim)
{
	if (nodeAnim->mNumRotationKeys == 1)
	{
		return nodeAnim->mRotationKeys[0].mValue;
	}

	int rotationIndex = FindRotation(animationTime, nodeAnim);
	int nextRotationIndex = rotationIndex + 1;
	assert(nextRotationIndex < nodeAnim->mNumRotationKeys);
	
	float delta_time = (float)(nodeAnim->mRotationKeys[nextRotationIndex].mTime - nodeAnim->mRotationKeys[rotationIndex].mTime);
	float factor = (animationTime - (float)nodeAnim->mRotationKeys[rotationIndex].mTime) / delta_time;

	assert(factor >= 0.0f && factor <= 1.0f);
	aiQuaternion startQuat = nodeAnim->mRotationKeys[rotationIndex].mValue;
	aiQuaternion endQuat = nodeAnim->mRotationKeys[nextRotationIndex].mValue;

	return NLerp(startQuat, endQuat, factor);
}

aiVector3D SkeletalMesh::CalcInterpolatedScaling(float animationTime, const aiNodeAnim* nodeAnim)
{
	if (nodeAnim->mNumScalingKeys == 1)
	{
		return nodeAnim->mScalingKeys[0].mValue;
	}

	int scalingIndex = FindScaling(animationTime, nodeAnim);
	int nextScalingIndex = scalingIndex + 1;
	assert(nextScalingIndex < nodeAnim->mNumScalingKeys);
	
	float deltaTime = (float)(nodeAnim->mScalingKeys[nextScalingIndex].mTime - nodeAnim->mScalingKeys[scalingIndex].mTime);
	float  factor = (animationTime - (float)nodeAnim->mScalingKeys[scalingIndex].mTime) / deltaTime;
	assert(factor >= 0.0f && factor <= 1.0f);
	
	aiVector3D start = nodeAnim->mScalingKeys[scalingIndex].mValue;
	aiVector3D end = nodeAnim->mScalingKeys[nextScalingIndex].mValue;
	aiVector3D delta = end - start;

	return start + factor * delta;
}

void SkeletalMesh::ReadNodeHierarchy(float animationTime, const aiNode* node, const aiMatrix4x4 parentTransform)
{
	std::string nodeName(node->mName.data);

	const aiAnimation* animation = scene->mAnimations[0];
	aiMatrix4x4 nodeTransform = node->mTransformation;

	const aiNodeAnim* nodeAnim = FindNodeAnim(animation, nodeName);

	if (nodeAnim)
	{

		aiVector3D scalingVector = CalcInterpolatedScaling(animationTime, nodeAnim);
		aiMatrix4x4 scalingMatr;
		aiMatrix4x4::Scaling(scalingVector, scalingMatr);

		aiQuaternion rotateQuat = CalcInterpolatedRotation(animationTime, nodeAnim);
		aiMatrix4x4 rotateMatr = aiMatrix4x4(rotateQuat.GetMatrix());

		aiVector3D translateVector = CalcInterpolatedPosition(animationTime, nodeAnim);
		aiMatrix4x4 translateMatr;
		aiMatrix4x4::Translation(translateVector, translateMatr);

		if (std::string(nodeAnim->mNodeName.data) == std::string("Head"))
		{
			aiQuaternion rotateHead = aiQuaternion(rotateHeadXZ.w, rotateHeadXZ.x, rotateHeadXZ.y, rotateHeadXZ.z);

			nodeTransform = translateMatr * (rotateMatr * aiMatrix4x4(rotateHead.GetMatrix())) * scalingMatr;
		}
		else
		{
			nodeTransform = translateMatr * rotateMatr * scalingMatr;
		}

	}

	aiMatrix4x4 globalTransform = parentTransform * nodeTransform;

	if (boneMapping.find(nodeName) != boneMapping.end()) // true if node_name exist in bone_mapping
	{
		int bone_index = boneMapping[nodeName];
		boneMatrices[bone_index].final_world_transform = globalInverseTransform * globalTransform * boneMatrices[bone_index].offset_matrix;
	}

	for (int i = 0; i < node->mNumChildren; i++)
	{
		ReadNodeHierarchy(animationTime, node->mChildren[i], globalTransform);
	}
}

void SkeletalMesh::BoneTransform(double timeInSec, std::vector<aiMatrix4x4>& transforms)
{
	aiMatrix4x4 identity_matrix;

	double timeInTicks = timeInSec * ticksPerSecond;
	float animationTime = fmod(timeInTicks, scene->mAnimations[0]->mDuration);

	ReadNodeHierarchy(animationTime, scene->mRootNode, identity_matrix);
	transforms.resize(numOfBones);

	for (int i = 0; i < numOfBones; i++)
	{
		transforms[i] = boneMatrices[i].final_world_transform;
	}
}
