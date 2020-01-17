#include "../Header/Engine.hpp"
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include "../Header/TextureManager.hpp"

SDL_Texture* playerTex;
SDL_Rect srcR, destR;

Engine::Engine()
{
}

Engine::~Engine()
{
}

void Engine::init()
{
	bool fullscreen = false;
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
			std::cout << "Renderer Created.\n";
		}
		isRunning = true;
	}
	else {
		isRunning = false;
	}

	textureManager = new TextureManager;
	playerTex = textureManager->LoadTexture("../Solution/Assets/player.png", renderer);
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
	++frameCounter;

	destR.h = 109;
	destR.w = 64;
	destR.x = frameCounter / 100;
}

void Engine::render()
{
	SDL_RenderClear(renderer);

	SDL_RenderCopy(renderer, playerTex, NULL, &destR);

	SDL_RenderPresent(renderer);
}

void Engine::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Window Cleaned.\n";
}

void Engine::run()
{
	
}

bool Engine::running()
{
	return isRunning;
}
