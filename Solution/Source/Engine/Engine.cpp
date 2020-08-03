#include <iostream>
#include <vector>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "Engine/Engine.hpp"
#include "ObjectSystem/Actor.hpp"
#include "ObjectSystem/ObjectManager.hpp"
#include "Input/InputSystem.hpp"
#include "glew.h"
#include "Graphics/Graphics2D.hpp"
#include "ObjectSystem/InputComponent.hpp"
#include "Graphics/Renderer.hpp"
#include "Graphics/VertexArray.hpp"
#include "Graphics/Shader.hpp"
#include "ObjectSystem/MeshComponent.hpp"
#include "Utils/Utils.hpp"
#include "Audio/AudioSystem.hpp"
#include "Physics/Physics.hpp"

#include "Temp/D3Level.hpp"
#include "Temp/D2Level.hpp"

Engine::Engine()
{
}

Engine::~Engine()
{

}

void Engine::Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("Unable to initialize SDL: %s", SDL_GetError());
		return;
	}

	if (TTF_Init() != 0) {
		printf("Failed to initialize SDL_ttf");
		return;
	}

	renderer = new Renderer(this);
	if (!renderer->Initialize(width, height)) {
		printf("Failed to initialize renderer");
		delete renderer;
		renderer = nullptr;
		return;
	}

	/*if (!audioSystem->Initialize()) {
		printf("Failed to initialize audioSystem");
		Clean();
	}*/

	ECS = new ObjectManager(this);
	//Graphics2DSystem = new Graphics2D(spriteShader, renderer);
	inputSystem = new InputSystem();
	physics = new Physics(this);
	isRunning = true;
	Run();
}

void Engine::Run()
{
	D2Level level(this);
	level.Load();
}

void Engine::HandleEvents()
{
	inputSystem->PrepareForUpdate();

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
	}
	inputSystem->Update();

	renderer->ProcessCanvasInput();
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
	//physics->Update(deltaTime);
}

void Engine::Render()
{
	renderer->Draw();
}

void Engine::Clean()
{
	//delete Graphics2DSystem;
	delete inputSystem;
	delete ECS;
	if (renderer) {
		renderer->Shutdown();
	}
	delete renderer;
	if (audioSystem) {
		//audioSystem->Shutdown();
	}
	delete audioSystem;
	delete physics;
	SDL_Quit();
	std::cout << "Window Cleaned.\n";
}

bool Engine::IsRunning()
{
	return isRunning;
}