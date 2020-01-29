#include "Input\Input.hpp"

Input::Input()
{
}

void Input::Update()
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
