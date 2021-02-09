#include "Graphics/SkeletalMesh.hpp"
#include <assimp/scene.h>
#include <cassert>

SkeletalMesh::SkeletalMesh(const aiMesh* mesh, const aiScene* scene)
{
	globalInverseTransform = scene->mRootNode->mTransformation;
	globalInverseTransform.Inverse();

	bones.resize(mesh->mNumVertices);
	int numBones = 0;
	for (int i = 0; i < mesh->mNumBones; ++i)
	{
		int boneIndex = 0;
		std::string boneName(mesh->mBones[i]->mName.data);

		if (boneMapping.find(boneName) == boneMapping.end())
		{
			boneIndex = numBones;
			numBones++;
			BoneMatrix bi;
			boneInfo.push_back(bi);
			boneInfo[boneIndex].offset_matrix = mesh->mBones[i]->mOffsetMatrix;
			boneMapping[boneName] = boneIndex;
		}
		else
		{
			boneIndex = boneMapping[boneName];
		}

		for (int j = 0; j < mesh->mBones[i]->mNumWeights; ++j)
		{
			int vertexID = mesh->mBones[i]->mWeights[j].mVertexId;
			float weight = mesh->mBones[i]->mWeights[j].mWeight;
			bones[vertexID].addBoneData(boneIndex, weight);
		}
	}

	InitNode(rootNode, scene->mRootNode);

	for (int i = 0; i < scene->mNumAnimations; ++i)
	{
		Animation animation;
		aiAnimation* sourceAnimation = scene->mAnimations[i];
		animation.ticksPerSecond = sourceAnimation->mTicksPerSecond;
		animation.duration = sourceAnimation->mDuration;

		for (int j = 0; j < sourceAnimation->mNumChannels; ++i)
		{
			NodeAnim nodeAnim;
			aiNodeAnim* sourceNodeAnim = sourceAnimation->mChannels[j];

			nodeAnim.name = sourceNodeAnim->mNodeName.data;
			for (unsigned int k = 0; k < sourceNodeAnim->mNumPositionKeys; ++k)
			{
				nodeAnim.positionKeys.push_back(sourceNodeAnim->mPositionKeys[k]);
			}
			for (unsigned int k = 0; k < sourceNodeAnim->mNumRotationKeys; ++k)
			{
				nodeAnim.rotationKeys.push_back(sourceNodeAnim->mRotationKeys[k]);
			}
			for (unsigned int k = 0; k < sourceNodeAnim->mNumScalingKeys; ++k)
			{
				nodeAnim.scalingKeys.push_back(sourceNodeAnim->mScalingKeys[k]);
			}
			animation.nodeAnims[nodeAnim.name] = nodeAnim;
		}
		animations.emplace_back(animation);
	}

}

void SkeletalMesh::Draw(Shader* shader)
{
	std::vector<aiMatrix4x4> transforms;


}

void SkeletalMesh::InitNode(Node& node, aiNode* sourceNode)
{
	node.name = sourceNode->mName.data;
	node.nodeTransformation = sourceNode->mTransformation;

	for (int i = 0; i < sourceNode->mNumChildren; ++i)
	{
		Node childNode;
		InitNode(childNode, sourceNode->mChildren[i]);
		node.children.push_back(childNode);
	}
}

void SkeletalMesh::BoneTransform(float timeInSeconds, std::vector<aiMatrix4x4>& transforms)
{
	aiMatrix4x4 identity;
	float TicksPerSecond = animations[0].ticksPerSecond != 0 ? animations[0].ticksPerSecond : 25.0f;
	float TimeInTicks = timeInSeconds * TicksPerSecond;
	float AnimationTime = fmod(TimeInTicks, animations[0].duration);

	ReadNodeHierarchy(AnimationTime, rootNode, identity);

	transforms.resize(bones.size());
	for (int i = 0; i < bones.size(); i++) {
		transforms[i] = boneInfo[i].final_world_transform;
	}
}

void SkeletalMesh::ReadNodeHierarchy(float animationTime, const Node& node, const aiMatrix4x4& parentTransform)
{
	Animation& animation = animations[0];
	aiMatrix4x4 NodeTransformation = node.nodeTransformation;

	if(animation.nodeAnims.find(node.name) != animation.nodeAnims.end())
	{
		NodeAnim& nodeAnim = animation.nodeAnims[node.name];
		aiVector3D scaling_vector = CalcInterpolatedScaling(animationTime, nodeAnim);
		aiMatrix4x4 scaling_matr;
		aiMatrix4x4::Scaling(scaling_vector, scaling_matr);

		aiQuaternion rotate_quat = CalcInterpolatedRotation(animationTime, nodeAnim);
		aiMatrix4x4 rotate_matr = aiMatrix4x4(rotate_quat.GetMatrix());

		aiVector3D translate_vector = CalcInterpolatedPosition(animationTime, nodeAnim);
		aiMatrix4x4 translate_matr;
		aiMatrix4x4::Translation(translate_vector, translate_matr);
		
		NodeTransformation = translate_matr * rotate_matr * scaling_matr;
	}

	aiMatrix4x4 GlobalTransformation = parentTransform * NodeTransformation;

	if (boneMapping.find(node.name) != boneMapping.end()) {
		int BoneIndex = boneMapping[node.name];
		boneInfo[BoneIndex].final_world_transform = globalInverseTransform * GlobalTransformation *
			boneInfo[BoneIndex].offset_matrix;
	}

	for (int i = 0; i < node.children.size(); i++) {
		ReadNodeHierarchy(animationTime, node.children[i], GlobalTransformation);
	}
}

aiVector3D SkeletalMesh::CalcInterpolatedPosition(float animationTime, const NodeAnim& nodeAnim)
{
	if (nodeAnim.positionKeys.size() == 1)
	{
		return nodeAnim.positionKeys[0].mValue;
	}

	int positionIndex = FindPosition(animationTime, nodeAnim);
	int nextPositionIndex = positionIndex + 1;
	assert(nextPositionIndex < nodeAnim.positionKeys.size());
	float deltaTime = (float)(nodeAnim.positionKeys[nextPositionIndex].mTime - nodeAnim.positionKeys[positionIndex].mTime);
	float factor = (animationTime - (float)nodeAnim.positionKeys[positionIndex].mTime) / deltaTime;
	assert(factor >= 0.0f && factor <= 1.0f);
	aiVector3D start = nodeAnim.positionKeys[positionIndex].mValue;
	aiVector3D end = nodeAnim.positionKeys[nextPositionIndex].mValue;
	aiVector3D delta = end - start;

	return start + factor * delta;
}

aiQuaternion SkeletalMesh::CalcInterpolatedRotation(float animationTime, const NodeAnim& nodeAnim)
{
	if (nodeAnim.rotationKeys.size() == 1)
	{
		return nodeAnim.rotationKeys[0].mValue;
	}

	int rotationIndex = FindRotation(animationTime, nodeAnim);
	int nextRotationIndex = rotationIndex + 1;
	assert(nextRotationIndex < nodeAnim.rotationKeys.size());
	float deltaTime = (float)(nodeAnim.rotationKeys[nextRotationIndex].mTime - nodeAnim.rotationKeys[rotationIndex].mTime);
	float factor = (animationTime - (float)nodeAnim.rotationKeys[rotationIndex].mTime) / deltaTime;

	assert(factor >= 0.0f && factor <= 1.0f);
	aiQuaternion startQuat = nodeAnim.rotationKeys[rotationIndex].mValue;
	aiQuaternion endQuat = nodeAnim.rotationKeys[nextRotationIndex].mValue;

	return NLerp(startQuat, endQuat, factor);
}

aiVector3D SkeletalMesh::CalcInterpolatedScaling(float animationTime, const NodeAnim& nodeAnim)
{
	if (nodeAnim.scalingKeys.size() == 1)
	{
		return nodeAnim.scalingKeys[0].mValue;
	}

	int scalingIndex = FindScaling(animationTime, nodeAnim);
	int nextScalingIndex = scalingIndex + 1;
	assert(nextScalingIndex < nodeAnim.scalingKeys.size());
	float deltaTime = (float)(nodeAnim.scalingKeys[nextScalingIndex].mTime - nodeAnim.scalingKeys[scalingIndex].mTime);
	float  factor = (animationTime - (float)nodeAnim.scalingKeys[scalingIndex].mTime) / deltaTime;
	assert(factor >= 0.0f && factor <= 1.0f);
	aiVector3D start = nodeAnim.scalingKeys[scalingIndex].mValue;
	aiVector3D end = nodeAnim.scalingKeys[nextScalingIndex].mValue;
	aiVector3D delta = end - start;

	return start + factor * delta;
}

int SkeletalMesh::FindScaling(float animationTime, const NodeAnim& nodeAnim)
{
	for (int i = 0; i < nodeAnim.positionKeys.size() - 1; i++)
	{
		if (animationTime < (float)nodeAnim.positionKeys[i + 1].mTime)
		{
			return i;
		}
	}
	assert(0);
	return 0;
}

int SkeletalMesh::FindRotation(float animationTime, const NodeAnim& nodeAnim)
{
	for (int i = 0; i < nodeAnim.rotationKeys.size() - 1; i++)
	{
		if (animationTime < (float)nodeAnim.rotationKeys[i + 1].mTime)
		{
			return i;
		}
	}
	assert(0);
	return 0;
}

int SkeletalMesh::FindPosition(float animationTime, const NodeAnim& nodeAnim)
{
	for (int i = 0; i < nodeAnim.scalingKeys.size() - 1; i++)
	{
		if (animationTime < (float)nodeAnim.scalingKeys[i + 1].mTime)
		{
			return i;
		}
	}
	assert(0);
	return 0;
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

Matrix4 SkeletalMesh::ToMat4(aiMatrix4x4 aiMatrix)
{
	Matrix4 mat4;
	mat4.mat[0][0] = aiMatrix.a1; mat4.mat[0][1] = aiMatrix.b1; mat4.mat[0][2] = aiMatrix.c1; mat4.mat[0][3] = aiMatrix.d1;
	mat4.mat[1][0] = aiMatrix.a2; mat4.mat[1][1] = aiMatrix.b2; mat4.mat[1][2] = aiMatrix.c2; mat4.mat[1][3] = aiMatrix.d2;
	mat4.mat[2][0] = aiMatrix.a3; mat4.mat[2][1] = aiMatrix.b3; mat4.mat[2][2] = aiMatrix.c3; mat4.mat[2][3] = aiMatrix.d3;
	mat4.mat[3][0] = aiMatrix.a4; mat4.mat[3][1] = aiMatrix.b4; mat4.mat[3][2] = aiMatrix.c4; mat4.mat[3][3] = aiMatrix.d4;
	return mat4;
}