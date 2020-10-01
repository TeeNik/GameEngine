#pragma once
#include "Math/Math.h"

class BoneTransform
{
public:
	Quaternion Rotation;
	Vector3 Translation;

	Matrix4 ToMatrix() const;

	static BoneTransform Interpolate(const BoneTransform& a, const BoneTransform& b, float f);
};
