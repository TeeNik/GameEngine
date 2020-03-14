#pragma once
#include "Input/KeyboardState.hpp"
#include "Input/InputSystem.hpp"

bool KeyboardState::GetKeyValye(SDL_Scancode keyCode) const
{
	return currState[keyCode] == 1;
}

ButtonState KeyboardState::GetKeyState(SDL_Scancode keyCode) const
{
	if (keyCode == SDL_SCANCODE_W) {
		currState[keyCode];
	}

	if (prevState[keyCode] == 0) {
		if (currState[keyCode] == 0) {
			return ButtonState::None;
		}
		else {
			return ButtonState::Pressed;
		}
	}
	else {
		if (currState[keyCode] == 0) {
			return ButtonState::Released;
		}
		else {
			return ButtonState::Held;
		}
	}
}