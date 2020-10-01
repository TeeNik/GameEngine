#include "Graphics/BoneTransform.hpp"

Matrix4 BoneTransform::ToMatrix() const
{
	Matrix4 rot = Matrix4::CreateFromQuaternion(Rotation);
	Matrix4 trans = Matrix4::CreateTranslation(Translation);

	return rot * trans;
}

BoneTransform BoneTransform::Interpolate(const BoneTransform& a, const BoneTransform& b, float f)
{
	BoneTransform retVal;
	retVal.Rotation = Quaternion::Slerp(a.Rotation, b.Rotation, f);
	retVal.Translation = Vector3::Lerp(a.Translation, b.Translation, f);
	return retVal;
}