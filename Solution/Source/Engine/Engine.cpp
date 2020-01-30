#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "TextureManager.hpp"
#include "Engine/Engine.hpp"
#include "ObjectSystem/Actor.hpp"
#include "ObjectSystem/SpriteRendererComponent.hpp"
#include "Input/Input.hpp"

Actor* player;

Engine::Engine()
{
}

Engine::~Engine()
{
}

void Engine::Init()
{
	InitWindow();

	player = ECS.CreateActor();
	player->AddComponent<SpriteRendererComponent>("../Solution/Assets/player.png", player);
}

void Engine::HandleEvents()
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
	Input.HandleEvents();
}

void Engine::Update()
{
	++frameCounter;
	SDL_RenderClear(renderer);
	ECS.Update();
	SDL_RenderPresent(renderer);

}

void Engine::Render()
{

	player->Render();

}

void Engine::Clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Window Cleaned.\n";
}

void Engine::Run()
{
	
}

bool Engine::IsRunning()
{
	return isRunning;
}

void Engine::InitWindow()
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
		TextureManager::SetRenderer(renderer);
		isRunning = true;
	}
	else {
		isRunning = false;
	}
}
