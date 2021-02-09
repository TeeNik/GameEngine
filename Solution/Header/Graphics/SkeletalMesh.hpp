#pragma once

#include <cstring>
#include <assimp/matrix4x4.h>
#include <string>
#include <vector>
#include <assimp/anim.h>
#include <map>
#include "Math/Math.h"

#define NUM_BONES_PER_VERTEX 4

class Shader;
struct aiNode;
struct aiMesh;
struct aiScene;

struct VertexBoneData
{
	int IDs[NUM_BONES_PER_VERTEX];
	float Weights[NUM_BONES_PER_VERTEX];

	VertexBoneData()
	{
		memset(IDs, 0, sizeof(IDs));    // init all values in array = 0
		memset(Weights, 0, sizeof(Weights));
	}

	void addBoneData(int boneId, float weight)
	{
		for (int i = 0; i < NUM_BONES_PER_VERTEX; i++)
		{
			if (Weights[i] == 0.0)
			{
				IDs[i] = boneId;
				Weights[i] = weight;
				return;
			}
		}
	}
};

struct BoneMatrix
{
	aiMatrix4x4 offset_matrix;
	aiMatrix4x4 final_world_transform;
};

struct Node
{
	std::string name;
	aiMatrix4x4 nodeTransformation;
	std::vector<Node> children;
};

struct NodeAnim
{
	std::string name;
	std::vector<aiVectorKey> positionKeys;
	std::vector<aiQuatKey> rotationKeys;
	std::vector<aiVectorKey> scalingKeys;
};

struct Animation
{
	std::string name;
	double ticksPerSecond;
	double duration;
	std::map<std::string, NodeAnim> nodeAnims;
};

class SkeletalMesh
{
public:
	SkeletalMesh(const aiMesh* mesh, const aiScene* scene);

	void Draw(Shader* shader);

private:
	Node rootNode;
	aiMatrix4x4 globalInverseTransform;
	std::vector<Animation> animations;
	std::map<std::string, int> boneMapping;
	std::vector<VertexBoneData> bones;
	std::vector<BoneMatrix> boneInfo;

	void InitNode(Node& node, aiNode* sourceNode);
	void BoneTransform(float timeInSeconds, std::vector<aiMatrix4x4>& transforms);
	void ReadNodeHierarchy(float animationTime, const Node& node, const aiMatrix4x4& parentTransform);

	aiVector3D CalcInterpolatedPosition(float animationTime, const NodeAnim& nodeAnim);
	aiQuaternion CalcInterpolatedRotation(float animationTime, const NodeAnim& nodeAnim);
	aiVector3D CalcInterpolatedScaling(float animationTime, const NodeAnim& nodeAnim);

	int FindPosition(float animationTime, const NodeAnim& nodeAnim);
	int FindRotation(float animationTime, const NodeAnim& nodeAnim);
	int FindScaling(float animationTime, const NodeAnim& nodeAnim);

	aiQuaternion NLerp(aiQuaternion a, aiQuaternion b, float blend);
	Matrix4 ToMat4(aiMatrix4x4 aiMatrix);
};