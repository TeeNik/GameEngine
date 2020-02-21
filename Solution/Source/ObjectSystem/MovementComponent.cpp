#include "ObjectSystem/MovementComponent.hpp"
#include "Math/Math.h"
#include "ObjectSystem/Actor.hpp"

MovementComponent::MovementComponent(Actor* o, int updateOrder) : 
	Component(o, updateOrder),
	angularSpeed(0),
	forwardSpeed(0)
{
}

void MovementComponent::Update(float deltaTime)
{
	if (!Math::NearZero(angularSpeed))
	{
		Quaternion rot = owner->GetActorRotation();
		float angle = angularSpeed * deltaTime;
		
		Quaternion inc(Vector3::UnitZ, angle);
		
		rot = Quaternion::Concatenate(rot, inc);
		owner->SetActorRotation(rot);
	}

	if (!Math::NearZero(forwardSpeed))
	{
		Vector3 pos = owner->GetActorLocation();
		pos += owner->GetForward() * forwardSpeed * deltaTime;
		owner->SetActorLocation(pos);
	}
}
