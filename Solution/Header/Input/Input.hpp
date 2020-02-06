#pragma once
#include <unordered_map>
#include <string>
#include <list>
#include <functional>
#include "SDL.h"
#include "Input\InputSubscriber.hpp"

class Input : public InputSubscriber {

public:

	Input();
	~Input();
	
	void HandleEvents();
	void Subscribe(int keyCode, std::function<void()>& func) override;

private:
	std::unordered_map<int, std::list<std::function<void()>>> eventsList;
	SDL_Event event;

};

