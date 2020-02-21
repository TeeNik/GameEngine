#pragma once
#include "ObjectSystem/Actor.hpp"

class Engine;

class Camera : public Actor {
public:
	Camera(Engine* e);

	virtual void Update(float deltaTime) override;
};