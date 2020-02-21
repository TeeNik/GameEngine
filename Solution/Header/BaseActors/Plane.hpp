#pragma once
#include "ObjectSystem/Actor.hpp"

class Plane;
class Vector3;
class MeshComponent;

class Plane : public Actor {
public:
	Plane(Engine* e);

protected:
	MeshComponent* mc;

private:
	Vector3 InitialScale{ 10, 10, 10 };
};