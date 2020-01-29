#pragma once
#include <unordered_map>
#include <string>
#include <functional>
#include "SDL.h"

class Input {


private:
	std::unordered_map<std::string, std::function<void()>> bindedEvents;
};

