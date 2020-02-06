#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "TextureManager.hpp"
#include "Engine/Engine.hpp"
#include "ObjectSystem/Actor.hpp"
#include "ObjectSystem/SpriteRendererComponent.hpp"
#include "ObjectSystem/ObjectManager.hpp"
#include "Input/Input.hpp"
#include "Graphics/Graphics2D.hpp"
#include "ObjectSystem/InputComponent.hpp"


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
	Graphics2DSystem = new Graphics2D(renderer);
	InputSystem = new Input();

	Run();
}

void Engine::Run()
{
	auto player = ECS->CreateActor();
	auto sprite = player->AddComponent<SpriteRendererComponent>("../Solution/Assets/adventurer.png");
	auto input = player->AddComponent<InputComponent>();
	player->SetActorLocation(Vector(sprite->GetTextureWidth()/2, sprite->GetTextureHeight()/2));
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
			SDL_SetRenderDrawColor(renderer, 0, 100, 100, 100);
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
		InputSystem->HandleEvents();
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
	
	
	ECS->Update(deltaTime);

}

void Engine::Render()
{
	SDL_RenderClear(renderer);
	Graphics2DSystem->Draw();
	SDL_RenderPresent(renderer);
}

void Engine::Clean()
{
	delete Graphics2DSystem;
	delete InputSystem;
	delete ECS;

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Window Cleaned.\n";
}



bool Engine::IsRunning()
{
	return isRunning;
}


