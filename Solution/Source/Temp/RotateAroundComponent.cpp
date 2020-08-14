#include "Temp/RotateAroundComponent.hpp"
#include "ObjectSystem/Actor.hpp"

RotateAroundComponent::RotateAroundComponent(Actor * owner) : Component(owner)
{
}

void RotateAroundComponent::Update(float deltaTime)
{
	angle += speed * deltaTime;
	Quaternion rotation(Vector3::UnitZ, angle);
	owner->SetActorRotation(rotation);
}

void RotateAroundComponent::SetRotation(const Vector3 & c, float s)
{
	center = c;
	speed = s;
}
