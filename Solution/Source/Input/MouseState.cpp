#pragma once
#include "Input/MouseState.hpp"
#include "Input/InputSystem.hpp"

bool MouseState::GetButtonValue(int button) const
{
	return (SDL_BUTTON(button) & currButtons) == 1;
}

ButtonState MouseState::GetButtonState(int button) const
{
	int mask = SDL_BUTTON(button);
	if ((mask & prevButtons) == 0)
	{
		if ((mask & currButtons) == 0)
		{
			return ButtonState::None;
		}
		else
		{
			return ButtonState::Pressed;
		}
	}
	else
	{
		if ((mask & currButtons) == 0)
		{
			return ButtonState::Released;
		}
		else
		{
			return ButtonState::Held;
		}
	}
}
