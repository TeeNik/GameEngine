#include "Input\ControllerState.hpp"

bool ControllerState::GetButtonValue(SDL_GameControllerButton button) const
{
	return currButtons[button] == 1;
}

ButtonState ControllerState::GetButtonState(SDL_GameControllerButton button) const
{
	if (prevButtons[button] == 0)
	{
		if (currButtons[button] == 0)
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
		if (currButtons[button] == 0)
		{
			return ButtonState::Released;
		}
		else
		{
			return ButtonState::Held;
		}
	}
}
