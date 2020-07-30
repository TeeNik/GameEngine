#include "ObjectSystem/Collision/BoxComponent.hpp"
#include "ObjectSystem/Actor.hpp"
#include "Engine/Engine.hpp"


BoxComponent::BoxComponent(Actor* o) : Component(o),
worldBox(Vector3::Zero, Vector3::Zero),
objectBox(Vector3::Zero, Vector3::Zero),
shouldRotate(true)
{
	updateOrder = 120;

	//owner->GetEngine().get
}

void BoxComponent::Update(float deltaTime)
{
	worldBox = objectBox;
	Vector3 scale = owner->GetActorScale();
	worldBox.min = worldBox.min * scale;
	worldBox.max = worldBox.max * scale;

	if (shouldRotate)
	{
		worldBox.Rotate(owner->GetActorRotation());
	}
}
