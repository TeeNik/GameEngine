#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "TextureManager.hpp"
#include "Engine/Engine.hpp"
#include "ObjectSystem/Actor.hpp"
#include "ObjectSystem/SpriteRendererComponent.hpp"
#include "Input/Input.hpp"
#include "ObjectSystem/InputComponent.hpp"

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

	ECS = new ObjectManager(this);

	player = ECS->CreateActor();
	player->AddComponent<SpriteRendererComponent>("../Solution/Assets/player.png");
	auto input = player->AddComponent<InputComponent>();
	input->BindKey(SDLK_UP, []() {std::cout << "Up\n"; });
}

void Engine::InitWindow()
{
	bool fullscreen = false;
	int flags = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Subsystems Initialised.\n";
		window = SDL_CreateWindow("GameEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		if (window) {
			std::cout << "Window Created.\n";
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
			std::cout << "Renderer Created.\n";
		}
		TextureManager::SetRenderer(renderer);
		isRunning = true;
	}
	else {
		isRunning = false;
	}
}

void Engine::HandleEvents()
{
	//TODO refactor
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		default:
			break;
		}
		const auto* state = SDL_GetKeyboardState(NULL);
		if (state[SDL_SCANCODE_ESCAPE]) {
			isRunning = false;
		}
		Input.HandleEvents();
	}
}

void Engine::Update()
{
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksCount + 16))
		;

	float deltaTime = (SDL_GetTicks() - ticksCount) / 1000.0f;
	if (deltaTime > deltaTimeLimit) {
		deltaTime = deltaTimeLimit;
	}
	ticksCount = SDL_GetTicks();
	
	SDL_RenderClear(renderer);
	ECS->Update(deltaTime);
	SDL_RenderPresent(renderer);

}

void Engine::Render()
{

	player->Render();

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}

void Engine::Clean()
{
	delete ECS;
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


