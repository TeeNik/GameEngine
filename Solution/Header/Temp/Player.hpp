#pragma once
#include "ObjectSystem/Actor.hpp"

class Engine;
class CameraComponent;
class MovementComponent;
class BoxComponent;

class Player : public Actor {

public:
	Player(Engine* e);

	virtual void Update(float deltaTime) override;

protected:
	CameraComponent* camera;
	MovementComponent* moveComp;
	BoxComponent* box;
};