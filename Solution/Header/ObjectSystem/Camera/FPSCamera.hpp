#pragma once
#include "CameraComponent.hpp"

class FPSCamera : public CameraComponent {
public:
	FPSCamera(Actor* o);

	virtual void Update(float deltaTime) override;

private:
	float pitchSpeed;
	float maxPitch;
	float pitch;
};