#pragma once
#include <unordered_map>
#include <string>
#include <list>
#include <functional>
#include "SDL.h"
#include "Input\InputSubscriber.hpp"
#include "KeyboardState.hpp"


enum class ButtonState {
	None,
	Pressed,
	Released,
	Held
};

struct InputState {
	KeyboardState Keybord;
};

class InputSystem : public InputSubscriber {

public:

	InputSystem();
	~InputSystem();

	bool Initialize();
	void Shutdown();

	void PrepareForUpdate();
	void Update();
	
	void HandleEvents();
	void Subscribe(int keyCode, std::function<void()>& func) override;
	inline const InputState& GetState() const { return state; }

private:
	InputState state;

	std::unordered_map<int, std::list<std::function<void()>>> eventsList;
	SDL_Event event;

};

