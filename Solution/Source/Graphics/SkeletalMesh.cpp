#include "Graphics/SkeletalMesh.hpp"
#include "assimp/scene.h"

SkeletalMesh::SkeletalMesh(const std::vector<Vertex>& v, const std::vector<unsigned>& ind) : Mesh(v, ind)
{
}

void SkeletalMesh::LoadAnimation(const aiScene* scene, aiMesh* m)
{
	globalInverseTransform = scene->mRootNode->mTransformation;
	globalInverseTransform.Inverse();

	const float sceneTicks = scene->mAnimations[0]->mTicksPerSecond;
	ticksPerSecond = sceneTicks != 0.0f ? sceneTicks : 25.0f;

	std::vector<VertexBoneData> bonesIdWeightsForEachVertex;

	printf("scene->HasAnimations() 1: %d\n", scene->HasAnimations());
	printf("scene->mNumMeshes 1: %d\n", scene->mNumMeshes);
	printf("scene->mAnimations[0]->mNumChannels 1: %d\n", scene->mAnimations[0]->mNumChannels);
	printf("scene->mAnimations[0]->mDuration 1: %f\n", scene->mAnimations[0]->mDuration);
	printf("scene->mAnimations[0]->mTicksPerSecond 1: %f\n", scene->mAnimations[0]->mTicksPerSecond);

	for (int i = 0; i < m->mNumBones; i++)
	{
		int boneIndex = 0;
		std::string bone_name(m->mBones[i]->mName.data);

		printf(m->mBones[i]->mName.data);

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
}
