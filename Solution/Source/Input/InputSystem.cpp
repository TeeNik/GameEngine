#include "Input\InputSystem.hpp"

InputSystem::InputSystem()
{
	state.Keyboard.currState = SDL_GetKeyboardState(NULL);
	memset(state.Keyboard.prevState, 0, SDL_NUM_SCANCODES);

	state.Mouse.currButtons = 0;
	state.Mouse.prevButtons = 0;

	controller = SDL_GameControllerOpen(0);
	//state.Controller.isConnected = controller != nullptr;
	//memset(state.Controller.currButtons, 0, SDL_CONTROLLER_BUTTON_MAX);
	//memset(state.Controller.prevButtons, 0, SDL_CONTROLLER_BUTTON_MAX);
}

InputSystem::~InputSystem()
{
}

void InputSystem::PrepareForUpdate()
{
	memcpy(state.Keyboard.prevState, state.Keyboard.currState, SDL_NUM_SCANCODES);

	state.Mouse.prevButtons = state.Mouse.currButtons;
	state.Mouse.isRelative = false;
	state.Mouse.scrollWheel = Vector2::Zero;

	//memcpy(state.Controller.prevButtons, state.Controller.currButtons, SDL_CONTROLLER_BUTTON_MAX);
}

void InputSystem::Update()
{
	int x = 0, y = 0;
	if (state.Mouse.isRelative)
	{
		state.Mouse.currButtons = SDL_GetRelativeMouseState(&x, &y);
	}
	else
	{
		state.Mouse.currButtons = SDL_GetMouseState(&x, &y);
	}

	state.Mouse.mousePos.x = static_cast<float>(x);
	state.Mouse.mousePos.y = static_cast<float>(y);

	for (int i = 0; i < SDL_CONTROLLER_BUTTON_MAX; i++)
	{
		//state.Controller.currButtons[i] = SDL_GameControllerGetButton(controller, SDL_GameControllerButton(i));
	}
}

void InputSystem::SetRelativeMouseMode(bool value)
{
	SDL_bool set = value ? SDL_TRUE : SDL_FALSE;
	SDL_SetRelativeMouseMode(set);

	state.Mouse.isRelative = value;
}

void InputSystem::HandleEvents()
{
	SDL_PollEvent(&event);
	if (event.type == SDL_KEYUP) {
		auto key = event.key.keysym.sym;
		if (eventsList.find(key) != eventsList.end()) {
			for (auto& func : eventsList[key])
			{
				func();
			}
		}
	}
}

void InputSystem::Subscribe(int keyCode, std::function<void()>& func)
{
	eventsList[keyCode].push_back(func);
}
