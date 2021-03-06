#include "Temp/Player2D.hpp"
#include "ObjectSystem/SpriteRendererComponent.hpp"
#include "ObjectSystem/AnimSpriteComponent.hpp"
#include "Utils/Utils.hpp"
#include "ObjectSystem/MovementComponent.hpp"
#include "Input/InputSystem.hpp"
#include "Engine/Engine.hpp"
#include "ObjectSystem/Collision/BoxComponent.hpp"

Player2D::Player2D(Engine * e) : Actor(e)
{
	//auto anim = AddComponent<AnimSpriteComponent>();
	//anim->SetSourceImage(Utils::ContructPath("girl.png"), 9, 5);
	//auto size = anim->GetSize();

	auto player = AddComponent<SpriteRendererComponent>();
	player->SetTexture(Utils::ContructPath("player.png"));
	auto size = Vector2(100,200);
	player->SetSize(size);
	SetActorPosition(Vector3(0, -200, 0));

	auto border = AddComponent<SpriteRendererComponent>();
	border->SetTexture(Utils::ContructPath("border.png"));
	border->SetSize(size);

	auto halfSize = Vector3(size.x, size.y, 0) * .5f;
	box = AddComponent<BoxComponent>();
	AABB aabb(halfSize * -1, halfSize);
	box->SetObjectBox(aabb);
	box->SetObjectType(CollisionObjectType::Dynamic);
	box->NextPos = GetActorPosition();
}

void Player2D::Update(float deltaTime)
{
	auto inputState = GetEngine()->GetInput()->GetState();
	auto keyboard = inputState.Keyboard;

	float vertical = 0.0f;
	float horizontal = 0.0f;

	const float speed = 200;

	if (keyboard.GetKeyState(SDL_Scancode::SDL_SCANCODE_W) == ButtonState::Held) {
		vertical += speed;
	}
	if (keyboard.GetKeyState(SDL_Scancode::SDL_SCANCODE_S) == ButtonState::Held) {
		vertical -= speed;
	}
	if (keyboard.GetKeyState(SDL_Scancode::SDL_SCANCODE_D) == ButtonState::Held) {
		horizontal += speed;
	}
	if (keyboard.GetKeyState(SDL_Scancode::SDL_SCANCODE_A) == ButtonState::Held) {
		horizontal -= speed;
	}

	if (!Math::NearZero(vertical) || !Math::NearZero(horizontal))
	{
		Vector3 pos = GetActorPosition();
		pos.x += horizontal * deltaTime;
		pos.y += vertical * deltaTime;
		box->NextPos = pos;
		//SetActorPosition(pos);
	}

	Actor::Update(deltaTime);
}
