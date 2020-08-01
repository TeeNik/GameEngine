#pragma once
#include "ObjectSystem/Actor.hpp"

class Vector3;
class MeshComponent;
class BoxComponent;

class PlaneActor : public Actor {
public:
	PlaneActor(Engine* e);

protected:
	MeshComponent* mc;
	BoxComponent* box;

private:
	Vector3 InitialScale{ 10, 10, 10 };
};