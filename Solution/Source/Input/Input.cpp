#include "Input\Input.hpp"

InputSubscriber* Input::subscriber = nullptr;

Input::Input()
{
	subscriber = this;
}

void Input::HandleEvents()
{
	SDL_PollEvent(&event);
	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {
		case SDLK_w:
			if (eventsList.find(SDLK_w) != eventsList.end()) {
				for (auto& func : eventsList[SDLK_w]) {
					func();
				}
			}
		}
	}
}

void Input::Subscribe(int keyCode, std::function<void()>& func)
{
}
