#pragma once
#include "Graphics/Mesh.hpp"
#include <unordered_map>
#include <string>
#include <vector>

class SkeletalMesh : public Mesh
{

private:
	std::unordered_map<std::string, int> bones;
	int numOfBones;
	std::vector<
};