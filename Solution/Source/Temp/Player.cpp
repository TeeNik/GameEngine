#include "Temp/Player.hpp"
#include "ObjectSystem/SpriteRendererComponent.hpp"
#include "Utils/Utils.hpp"
#include "Engine/Engine.hpp"
#include "Input/InputSystem.hpp"
#include "ObjectSystem/Camera/FollowCamera.hpp"
#include "ObjectSystem/Camera/FPSCamera.hpp"
#include "ObjectSystem/MovementComponent.hpp"
#include "ObjectSystem/Collision/BoxComponent.hpp"

#include <iostream>

Player::Player(Engine* e) : Actor(e)
{
	SetActorPosition(Vector3(-50, 0, 50));
	camera = AddComponent<FPSCamera>();
	moveComp = AddComponent<MovementComponent>();
	box = AddComponent<BoxComponent>();

	AABB bounds(Vector3(-25.0f, -25.0f, -87.5f), Vector3(25.0f, 25.0f, 87.5f));
	box->SetObjectBox(bounds);
	box->SetObjectType(CollisionObjectType::Dynamic);

	//SetActorScale(Vector3(.5f, .5f, 1));
	//auto sprite = new SpriteRendererComponent(Utils::ContructPath("player.png"), this);
	//SetActorLocation(Vector3(sprite->GetTextureWidth() / 2, sprite->GetTextureHeight() / 2, 0));
}

void Player::Update(float deltaTime)
{
	Actor::Update(deltaTime);
}
