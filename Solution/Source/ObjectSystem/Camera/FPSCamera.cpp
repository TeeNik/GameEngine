#include "ObjectSystem/Camera/FPSCamera.hpp"
#include "ObjectSystem/Actor.hpp"
#include "SDL.h"
#include "Input/InputSystem.hpp"
#include "Engine/Engine.hpp"

FPSCamera::FPSCamera(Actor* o) : CameraComponent(o)
{

}

void FPSCamera::Update(float deltaTime)
{
	CameraComponent::Update(deltaTime);

	Vector3 cameraPos = owner->GetActorPosition();
	
	auto mouse = owner->GetEngine()->GetInput()->GetState().Mouse;
	auto mousePos = mouse.GetPosition();

	int y = mousePos.y;
	const int maxMouseSpeed = 500;
	const float maxPitchSpeed = Math::Pi * 8;
	float pitchSpeed = 0.0f;
	if (y != 0)
	{
		pitchSpeed = static_cast<float>(y) / maxMouseSpeed * maxPitchSpeed;
	}

	pitch += pitchSpeed * deltaTime;
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
