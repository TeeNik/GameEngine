#pragma once
#include "ObjectSystem/Actor.hpp"

class Engine;
class CameraComponent;
class MovementComponent;

class Player : public Actor {

public:
	Player(Engine* e);

	virtual void Update(float deltaTime) override;

protected:
	CameraComponent* camera;
	MovementComponent* moveComp;

};