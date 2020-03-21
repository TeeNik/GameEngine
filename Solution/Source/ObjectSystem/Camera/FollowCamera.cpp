#include "ObjectSystem/Camera/FollowCamera.hpp"
#include "ObjectSystem/Actor.hpp"

FollowCamera::FollowCamera(Actor* o) : CameraComponent(o)
{
}

void FollowCamera::Update(float deltaTime)
{
	CameraComponent::Update(deltaTime);

	float dampening = 2 * Math::Sqrt(springConstant);
	Vector3 idealPos = ComputeCameraPos();
	Vector3 diff = actualPos - idealPos;
	Vector3 acel = -springConstant * diff - dampening * velocity;
	velocity += acel * deltaTime;
	actualPos += velocity * deltaTime;
	Vector3 target = owner->GetActorPosition() + owner->GetForward() * targetDist;
	Matrix4 view = Matrix4::CreateLookAt(actualPos, target, Vector3::UnitZ);
	SetViewMatrix(view);
}

void FollowCamera::SnapToIdeal()
{
	actualPos = ComputeCameraPos();
	velocity = Vector3::Zero;
	Vector3 target = owner->GetActorPosition() + owner->GetForward() * targetDist;
	Matrix4 view = Matrix4::CreateLookAt(actualPos, target,	Vector3::UnitZ);
	SetViewMatrix(view);
}

Vector3 FollowCamera::ComputeCameraPos() const
{
	Vector3 cameraPos = owner->GetActorPosition();
	cameraPos -= owner->GetForward() * horzDist;
	cameraPos += Vector3::UnitZ * vertDist;
	return cameraPos;
}
