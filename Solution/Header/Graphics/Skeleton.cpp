#pragma once
#include "Graphics/Skeleton.hpp"
#include <assimp/mesh.h>

bool Skeleton::Load(const aiMesh* mesh)
{
	int count = mesh->mNumBones;
	Bones.reserve(count);

	Bone temp;
	for(int i = 0; i < count; ++i)
	{
		const auto bone = mesh->mBones[i];
		temp.Name = bone->mName.C_Str();
	}

	Bones.emplace_back(temp);

	ComputeGlobalInvBindPose();

	return true;
}

void Skeleton::ComputeGlobalInvBindPose()
{
}
