#pragma once
#include "Graphics/BoneTransform.hpp"
#include <string>
#include <vector>

struct aiMesh;
const size_t MAX_SKELETON_BONES = 96;

struct MatrixPalette
{
	Matrix4 mEntry[MAX_SKELETON_BONES];
};

class Skeleton
{
public:
	struct Bone
	{
		BoneTransform LocalBindPose;
		std::string Name;
		int Parent;
	};

	bool Load(const aiMesh* mesh);

	size_t GetNumBones() const { return Bones.size(); }
	const Bone& GetBone(size_t idx) const { return Bones[idx]; }
	const std::vector<Bone>& GetBones() const { return Bones; }
	const std::vector<Matrix4>& GetGlobalInvBindPoses() const { return GlobalInvBindPoses; }
protected:
	void ComputeGlobalInvBindPose();
private:
	std::vector<Bone> Bones;
	std::vector<Matrix4> GlobalInvBindPoses;
};