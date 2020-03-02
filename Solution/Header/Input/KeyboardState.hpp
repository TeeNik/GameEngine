#pragma once
#include "SDL_scancode.h"

class KeyboardState {
public:
	friend class InputSystem;
	bool GetKeyValye(SDL_Scancode keyCode) const;
	ButtonState GetKeyState(SDL_Scancode keyCode) const;

private:
	const Uint8* currState;
	Uint8 prevState[SDL_NUM_SCANCODES];
};