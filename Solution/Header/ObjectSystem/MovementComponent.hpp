#pragma once
#include "ObjectSystem/Component.hpp"

class MovementComponent : public Component {

public:
	MovementComponent(Actor* o);
	virtual void Update(float deltaTime) override;

	float GetAngularSpeed() const { return angularSpeed; }
	float GetForwardSpeed() const { return forwardSpeed; }
	void SetAngularSpeed(float speed) { angularSpeed = speed; }
	void SetForwardSpeed(float speed) { forwardSpeed = speed; }
private:
	float angularSpeed;
	float forwardSpeed;
};