#pragma once
#include "SDL_gamecontroller.h"
#include "Input/InputSystem.hpp"
#include "Math/Math.h"

class ControllerState {
public:
	friend class InputSystem;

	bool GetButtonValue(SDL_GameControllerButton button) const;
	ButtonState GetButtonState(SDL_GameControllerButton button) const;

	inline const Vector2& GetLeftStick() const { return leftStick; }
	inline const Vector2& GetRightStick() const { return rightStick; }
	inline float GetLeftTrigger() const { return leftTrigger; }
	inline float GetRightTrigger() const { return rightTrigger; }

	bool GetIsConnected() const { return isConnected; }
private:
	Uint8 currButtons[SDL_CONTROLLER_BUTTON_MAX];
	Uint8 prevButtons[SDL_CONTROLLER_BUTTON_MAX];
	
	Vector2 leftStick;
	Vector2 rightStick;
	
	float leftTrigger;
	float rightTrigger;
	
	bool isConnected;
};
