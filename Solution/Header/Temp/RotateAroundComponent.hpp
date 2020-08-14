#pragma once
#include "ObjectSystem/Component.hpp"
#include"Math/Math.h"

class RotateAroundComponent : public Component
{
public:
	RotateAroundComponent(Actor* owner);
	virtual void Update(float deltaTime) override;
	void SetRotation(const Vector3& center, float speed);

private:
	Vector3 center;
	float speed;
	float angle;
};