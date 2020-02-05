#pragma once
#include "BaseStructs/Vector.hpp"

struct Transform {

	Vector position;
	Vector rotation;
	Vector scale = { 1,1,1 };

	Transform();
};