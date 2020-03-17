#include "ObjectSystem/Camera/FPSCamera.hpp"
#include "ObjectSystem/Actor.hpp"
#include "SDL.h"

FPSCamera::FPSCamera(Actor* o) : CameraComponent(o)
{

}

void FPSCamera::Update(float deltaTime)
{
	CameraComponent::Update(deltaTime);

	Vector3 cameraPos = owner->GetActorPosition();
	
	int x, y;
	SDL_GetRelativeMouseState(&x, &y);
	printf("%d %d\n", x, y);
	const int maxMouseSpeed = 500;
	const float maxPitchSpeed = Math::Pi * 8;
	float pitchSpeed = 0.0f;
	if (y != 0)
	{
		pitchSpeed = static_cast<float>(y) / maxMouseSpeed * maxPitchSpeed;
	}

	pitch += pitchSpeed * deltaTime;
	printf("%f", pitch);
	if (pitch > maxPitch) {
		10 + 5;
	}

	pitch = Math::Clamp(pitch, -maxPitch, maxPitch);

	Quaternion q(owner->GetRight(), pitch);
	Vector3 viewForward = Vector3::Transform(owner->GetForward(), q);
	Vector3 target = cameraPos + viewForward * 100;
	Vector3 up = Vector3::Transform(Vector3::UnitZ, q);
	Matrix4 view = Matrix4::CreateLookAt(cameraPos, target, up);
	SetViewMatrix(view);
}
