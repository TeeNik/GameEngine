#include "../Header/Engine.hpp"
#include "SDL.h"
#include <iostream>

Engine::Engine()
{
}

Engine::~Engine()
{
}

void Engine::init()
{
	bool fullscreen = true;
	int flags = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Subsystems Initialised.\n";
		window = SDL_CreateWindow("GameEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, flags);
		if (window) {
			std::cout << "Window Created.\n";
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Window Created.\n";
		}
		isRunning = true;
	}
	else {
		isRunning = false;
	}
}

void Engine::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		default:
			break;
	}
}

void Engine::update()
{
}

void Engine::render()
{
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
}

void Engine::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Window Cleaned.\n";
}

bool Engine::running()
{
	return isRunning;
}
