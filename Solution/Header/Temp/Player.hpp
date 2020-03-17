#pragma once
#include "ObjectSystem/Actor.hpp"

class Engine;
class FPSCamera;
class MovementComponent;

class Player : public Actor {

public:
	Player(Engine* e);

	virtual void Update(float deltaTime) override;

protected:
	FPSCamera* camera;
	MovementComponent* moveComp;

};