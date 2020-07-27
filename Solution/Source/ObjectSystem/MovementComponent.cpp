#include "ObjectSystem/MovementComponent.hpp"
#include "Math/Math.h"
#include "ObjectSystem/Actor.hpp"
#include "SDL.h"
#include "Engine/Engine.hpp"
#include "Input/InputSystem.hpp"

MovementComponent::MovementComponent(Actor* o) : 
	Component(o),
	angularSpeed(0),
	forwardSpeed(0)
{
	updateOrder = 10;
	o->GetEngine()->GetInput()->SetRelativeMouseMode(true);
}

void MovementComponent::Update(float deltaTime)
{
	auto inputState = owner->GetEngine()->GetInput()->GetState();
	auto keyboard = inputState.Keyboard;
	auto mouse = inputState.Mouse;

	float forwardSpeed = 0.0f;
	float strafeSpeed = 0.0f;
	if (keyboard.GetKeyState(SDL_Scancode::SDL_SCANCODE_W) == ButtonState::Held) {
		forwardSpeed += 400.0f;
	}
	if (keyboard.GetKeyState(SDL_Scancode::SDL_SCANCODE_S) == ButtonState::Held) {
		forwardSpeed -= 400.0f;
	}
	if (keyboard.GetKeyState(SDL_Scancode::SDL_SCANCODE_D) == ButtonState::Held) {
		strafeSpeed += 400.0f;
	}
	if (keyboard.GetKeyState(SDL_Scancode::SDL_SCANCODE_A) == ButtonState::Held) {
		strafeSpeed -= 400.0f;
	}

	auto mousePos = mouse.GetPosition();
	int x = mousePos.x;
	int y = mousePos.y;

	const int maxMouseSpeed = 500;
	const float maxAngularSpeed = Math::Pi * 8;
	float angularSpeed = 0;
	if (x != 0) {
		angularSpeed = static_cast<float>(x) / maxMouseSpeed * maxAngularSpeed;
	}

	if (!Math::NearZero(angularSpeed))
	{
		Quaternion rot = owner->GetActorRotation();
		float angle = angularSpeed * deltaTime;
		Quaternion inc(Vector3::UnitZ, angle);
		rot = Quaternion::Concatenate(rot, inc);
		owner->SetActorRotation(rot);
	}

	if (!Math::NearZero(forwardSpeed) || !Math::NearZero(strafeSpeed))
	{
		Vector3 pos = owner->GetActorPosition();
		pos += owner->GetForward() * forwardSpeed * deltaTime;
		pos += owner->GetRight() * strafeSpeed * deltaTime;
		owner->SetActorPosition(pos);
	}
}
