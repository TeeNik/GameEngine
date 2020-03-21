#pragma once

#include "ObjectSystem/Camera/CameraComponent.hpp"

class FollowCamera : public CameraComponent {
public:
	FollowCamera(class Actor* owner);

	void Update(float deltaTime) override;

	void SnapToIdeal();

	void SetHorzDist(float dist) { horzDist = dist; }
	void SetVertDist(float dist) { vertDist = dist; }
	void SetTargetDist(float dist) { targetDist = dist; }
	void SetSpringConstant(float spring) { springConstant = spring; }
private:
	Vector3 ComputeCameraPos() const;

	Vector3 actualPos;
	Vector3 velocity;
	float horzDist = 300;
	float vertDist = 150;
	float targetDist = 100;
	float springConstant = 64;
};