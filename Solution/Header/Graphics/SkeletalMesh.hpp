#pragma once
#include "Graphics/Mesh.hpp"
#include <unordered_map>
#include <string>
#include <vector>
#include "Math/Math.h"
#include <assimp\matrix4x4.h>
#include <glew.h>
#include <assimp/quaternion.h>


struct aiNode;
struct aiAnimation;

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

struct aiNodeAnim;
struct aiScene;
struct aiMesh;

class SkeletalMesh : public Mesh
{
	static const unsigned int MAX_BONES = 100;

public:
	SkeletalMesh(const std::vector<Vertex>& v, const std::vector<unsigned int>& ind);

	void LoadAnimation(const aiScene* scene, aiMesh* m);

private:
	std::unordered_map<std::string, int> boneMapping;
	int numOfBones;
	std::vector<BoneMatrix> boneMatrices;
	aiMatrix4x4 globalInverseTransform;

	GLuint boneLocation[MAX_BONES];
	float ticksPerSecond = 0.0f;

	int FindPosition(float animationTime, const aiNodeAnim* nodeAnim);
	int FindRotation(float animationTime, const aiNodeAnim* nodeAnim);
	int FindScaling(float animationTime, const aiNodeAnim* nodeAnim);
	const aiNodeAnim* FindNodeAnim(const aiAnimation* animation, const std::string nodeName);
	// calculate transform matrix
	aiVector3D CalcInterpolatedPosition(float animationTime, const aiNodeAnim* nodeAnim);
	aiQuaternion CalcInterpolatedRotation(float animationTime, const aiNodeAnim* nodeAnim);
	aiVector3D CalcInterpolatedScaling(float animationTime, const aiNodeAnim* nodeAnim);

	void ReadNodeHierarchy(float animationTime, const aiNode* node, const aiMatrix4x4 parentTransform);
	void BoneTransform(double timeInSec, std::vector<aiMatrix4x4>& transforms);

	void ReadNodeHierarchy(float animationTime, const aiNode* node, const aiMatrix4x4 parentTransform);
	void BoneTransform(double time_timeInSecin_sec, std::vector<aiMatrix4x4>& transforms);
};
