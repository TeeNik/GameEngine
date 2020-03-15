#include "ObjectSystem/Camera/FPSCamera.hpp"
#include "ObjectSystem/Actor.hpp"

FPSCamera::FPSCamera(Actor* o) : CameraComponent(o)
{

}

void FPSCamera::Update(float deltaTime)
{
	CameraComponent::Update(deltaTime);

	Vector3 cameraPos = owner->GetActorPosition();
	

	pitch += pitchSpeed * deltaTime;
	pitch = Math::Clamp(pitch, -maxPitch, maxPitch);

	Quaternion q(owner->GetRight(), pitch);
	Vector3 viewForward = Vector3::Transform(owner->GetForward(), q);
	Vector3 target = cameraPos + viewForward * 100;
	Vector3 up = Vector3::Transform(Vector3::UnitZ, q);
	Matrix4 view = Matrix4::CreateLookAt(cameraPos, target, up);
	SetViewMatrix(view);
}
