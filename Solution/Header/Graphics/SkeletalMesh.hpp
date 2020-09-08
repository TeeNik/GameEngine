#pragma once
#include "Graphics/Mesh.hpp"
#include <unordered_map>
#include <string>
#include <vector>
#include "Math/Math.h"
#include <assimp\matrix4x4.h>
#include <glew.h>

struct BoneMatrix
{
	aiMatrix4x4 offset_matrix;
	aiMatrix4x4 final_world_transform;
};

#define NUM_BONES_PER_VEREX 4

struct VertexBoneData
{
	unsigned int ids[NUM_BONES_PER_VEREX];
	float weights[NUM_BONES_PER_VEREX];

	VertexBoneData()
	{
		memset(ids, 0, sizeof(ids));    // init all values in array = 0
		memset(weights, 0, sizeof(weights));
	}

	void addBoneData(unsigned int boneId, float weight)
	{
		for(int i = 0; i < NUM_BONES_PER_VEREX; ++i)
		{
			if(weights[i] == 0)
			{
				ids[i] = boneId;
				weights[i] = weight;
				return;
			}
		}
	}
};

class SkeletalMesh : public Mesh
{
public:
	static const unsigned int MAX_BONES = 100;

private:
	std::unordered_map<std::string, int> boneMapping;
	int numOfBones;
	std::vector<BoneMatrix> boneMatrices;
	aiMatrix4x4 globalInverseTransform;

	GLuint boneLocation[MAX_BONES];
	float ticksPerSecond = 0.0f;
};