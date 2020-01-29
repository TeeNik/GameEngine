#pragma once
#include <unordered_map>
#include <string>
#include <list>
#include <functional>
#include "SDL.h"

class Input {

public:

	Input();

	void Update();


private:
	std::unordered_map<int, std::list<std::function<void()>>> eventsList;
	SDL_Event event;
};

