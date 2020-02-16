#pragma once
#include "Math/Math.h"

struct Transform {

	Vector3 position;
	Quaternion rotation;
	Vector3 scale;

	Transform();
};