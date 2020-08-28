#pragma once
#include "ObjectSystem/Actor.hpp"

class Engine;
class BoxComponent;

class Player2D : public Actor
{
public:
	Player2D(Engine* e);
	virtual void Update(float deltaTime) override;

private:
	BoxComponent* box;
};