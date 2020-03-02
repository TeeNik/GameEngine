#pragma once
#include <unordered_map>
#include <string>
#include <list>
#include <functional>
#include "SDL.h"
#include "Input\InputSubscriber.hpp"
#include "KeyboardState.hpp"
#include "MouseState.hpp"
#include "ControllerState.hpp"

enum class ButtonState {
	None,
	Pressed,
	Released,
	Held
};

struct InputState {
	KeyboardState Keyboard;
	MouseState Mouse;
	ControllerState Controller;
};

class InputSystem : public InputSubscriber {

public:

	InputSystem();
	~InputSystem();

	void PrepareForUpdate();
	void Update();

	void SetRelativeMouseMode(bool value);
	
	void HandleEvents();
	void Subscribe(int keyCode, std::function<void()>& func) override;
	inline const InputState& GetState() const { return state; }

private:
	InputState state;
	SDL_GameController* controller;

	std::unordered_map<int, std::list<std::function<void()>>> eventsList;
	SDL_Event event;

};

