#include <iostream>
#include <vector>
#include "SDL.h"
#include "SDL_image.h"
#include "Engine/Engine.hpp"
#include "ObjectSystem/Actor.hpp"
#include "ObjectSystem/AnimSpriteComponent.hpp"
#include "ObjectSystem/ObjectManager.hpp"
#include "Input/Input.hpp"
#include "glew.h"
#include "Graphics/Graphics2D.hpp"
#include "ObjectSystem/InputComponent.hpp"

#include "Graphics/VertexArray.hpp"
#include "Graphics/Shader.hpp"

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
	player->SetActorScale(Vector(3, 3, 3));
	auto sprite = new AnimSpriteComponent("../Solution/Assets/adventurer.png", 7, 11, player);
	auto input = new InputComponent(player);
	player->SetActorLocation(Vector(sprite->GetTextureWidth()/2, sprite->GetTextureHeight()/2));
	input->BindKey(SDLK_UP, []() {std::cout << "Up\n"; });
}

//TODO refactor
void Engine::InitWindow()
{
	bool fullscreen = false;
	int flags = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Subsystems Initialised.\n";

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

		window = SDL_CreateWindow("GameEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
		if (window) {
			std::cout << "Window Created.\n";
		}
		context = SDL_GL_CreateContext(window);
		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK) {
			std::cout << "Failed init glew!\n";
		}

		glGetError();

		if (!LoadShaders()) {
			std::cout << "Failed to load shaders.";
		}
		CreateSpriteVerts();

		isRunning = true;
	}
	else {
		isRunning = false;
	}
}

void Engine::CreateSpriteVerts()
{
	float vertices[] = {
		-0.5f,  0.5f, 0.f, 0.f, 0.f, // top left
		 0.5f,  0.5f, 0.f, 1.f, 0.f, // top right
		 0.5f, -0.5f, 0.f, 1.f, 1.f, // bottom right
		-0.5f, -0.5f, 0.f, 0.f, 1.f  // bottom left
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	spriteVerts = new VertexArray(vertices, 4, indices, 6);
}

bool Engine::LoadShaders()
{
	spriteShader = new Shader();
	bool isLoaded = spriteShader->Load("../Solution/Assets/Shaders/Basic.vert",
		"../Solution/Assets/Shaders/Basic.frag");
	if (!isLoaded) {
		return false;
	}
	spriteShader->SetActive();
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
	glClearColor(.8f, .8f, .8f, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	//draw

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//call Graphycs3D

	SDL_GL_SwapWindow(window);
}

void Engine::Clean()
{
	delete Graphics2DSystem;
	delete InputSystem;
	delete ECS;

	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Window Cleaned.\n";
}



bool Engine::IsRunning()
{
	return isRunning;
}


