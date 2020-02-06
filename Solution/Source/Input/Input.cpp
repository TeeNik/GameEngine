#include "Input\Input.hpp"

Input::Input()
{
}

Input::~Input()
{
}

void Input::HandleEvents()
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

void Input::Subscribe(int keyCode, std::function<void()>& func)
{
	eventsList[keyCode].push_back(func);
}
