#include "Temp/Player.hpp"
#include "ObjectSystem/SpriteRendererComponent.hpp"
#include "Utils/Utils.hpp"
#include "Engine/Engine.hpp"
#include "Input/InputSystem.hpp"

#include <iostream>

Player::Player(Engine* e) : Camera(e)
{
	SetActorPosition(Vector3(-50, 0, 0));
	//SetActorScale(Vector3(.5f, .5f, 1));
	//auto sprite = new SpriteRendererComponent(Utils::ContructPath("player.png"), this);
	//SetActorLocation(Vector3(sprite->GetTextureWidth() / 2, sprite->GetTextureHeight() / 2, 0));
}

void Player::Update(float deltaTime)
{
	Camera::Update(deltaTime);

	auto keyboard = GetEngine()->GetInput()->GetState().Keyboard;
	if (keyboard.GetKeyState(SDL_Scancode::SDL_SCANCODE_W) == ButtonState::Held) {
		transform.position += Vector3(1, 0, 0);
	}
	if (keyboard.GetKeyState(SDL_Scancode::SDL_SCANCODE_S) == ButtonState::Held) {
		transform.position -= Vector3(1, 0, 0);
	}
	if (keyboard.GetKeyState(SDL_Scancode::SDL_SCANCODE_D) == ButtonState::Held) {
		transform.position += Vector3(0, 1, 0);
	}
	if (keyboard.GetKeyState(SDL_Scancode::SDL_SCANCODE_A) == ButtonState::Held) {
		transform.position -= Vector3(0, 1, 0);
	}

	int x, y;
	SDL_GetRelativeMouseState(&x, &y);

	const int maxMouseSpeed = 500;
	const float maxAngularSpeed = Math::Pi * 8;
	float angularSpeed = 0;
	if (x != 0) {
		angularSpeed = static_cast<float>(x) / maxMouseSpeed * maxAngularSpeed;
	}
	const float maxPitchSpeed = Math::Pi * 8;
	float pitchSpeed = 0.0f;
	if (y != 0)
	{
		pitchSpeed = static_cast<float>(y) / maxMouseSpeed * maxPitchSpeed;
	}

}
