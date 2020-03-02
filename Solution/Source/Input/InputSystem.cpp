#include "Input\InputSystem.hpp"

InputSystem::InputSystem()
{
}

InputSystem::~InputSystem()
{
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
