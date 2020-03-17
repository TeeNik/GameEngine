#pragma once
#include "CameraComponent.hpp"

class FPSCamera : public CameraComponent {
public:
	FPSCamera(Actor* o);

	virtual void Update(float deltaTime) override;

	inline void SetPitchSpeed(float speed) { pitchSpeed = speed; }

private:
	float pitchSpeed = 0;
	float maxPitch = 60;
	float pitch = 0;
};