#pragma once
#include "BaseActors/Camera.hpp"

class Engine;

class Player : public Camera {

public:
	Player(Engine* e);

	virtual void Update(float deltaTime) override;

};