#include <iostream>
#include <vector>
#include "SDL.h"
#include "SDL_image.h"
#include "Engine/Engine.hpp"
#include "ObjectSystem/Actor.hpp"
#include "ObjectSystem/AnimSpriteComponent.hpp"
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

#include "BaseActors/Plane.hpp"
#include "BaseActors/Camera.hpp"

#include "Temp/Player.hpp"

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
	}

	renderer = new Renderer(this);
	if (!renderer->Initialize(width, height)) {
		printf("Failed to initialize renderer");
		delete renderer;
		renderer = nullptr;
	}
	/*if (!audioSystem->Initialize()) {
		printf("Failed to initialize audioSystem");
		Clean();
	}*/

	ECS = new ObjectManager(this);
	//Graphics2DSystem = new Graphics2D(spriteShader, renderer);
	inputSystem = new InputSystem();
	isRunning = true;
	Run();
}

void Engine::Run()
{
	//auto player = ECS->SpawnActor<Player>();

	Actor* a = ECS->SpawnActor<Actor>();
	a->SetActorLocation(Vector3(200.0f, 75.0f, 0.0f));
	a->SetActorScale(Vector3(100,100,100));
	Quaternion q(Vector3::UnitY, -Math::PiOver2);
	q = Quaternion::Concatenate(q, Quaternion(Vector3::UnitZ, Math::Pi + Math::Pi / 4.0f));
	a->SetActorRotation(q);
	MeshComponent* mc = new MeshComponent(a);
	mc->SetMesh(renderer->GetMesh(Utils::ContructPath("Cube.gpmesh")));

	a = ECS->SpawnActor<Actor>();
	a->SetActorLocation(Vector3(200.0f, -75.0f, 0.0f));
	a->SetActorScale(Vector3(3,3,3));
	mc = new MeshComponent(a);
	mc->SetMesh(renderer->GetMesh(Utils::ContructPath("Sphere.gpmesh")));

	// Setup floor
	const float start = -1250.0f;
	const float size = 250.0f;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			a = ECS->SpawnActor<Plane>();
			a->SetActorLocation(Vector3(start + i * size, start + j * size, -100.0f));
		}
	}

	// Left/right walls
	q = Quaternion(Vector3::UnitX, Math::PiOver2);
	for (int i = 0; i < 10; i++)
	{
		a = ECS->SpawnActor<Plane>();
		a->SetActorLocation(Vector3(start + i * size, start - size, 0.0f));
		a->SetActorRotation(q);

		a = ECS->SpawnActor<Plane>();
		a->SetActorLocation(Vector3(start + i * size, -start + size, 0.0f));
		a->SetActorRotation(q);
	}

	q = Quaternion::Concatenate(q, Quaternion(Vector3::UnitZ, Math::PiOver2));
	// Forward/back walls
	for (int i = 0; i < 10; i++)
	{
		a = ECS->SpawnActor<Plane>();
		a->SetActorLocation(Vector3(start - size, start + i * size, 0.0f));
		a->SetActorRotation(q);

		a = ECS->SpawnActor<Plane>();
		a->SetActorLocation(Vector3(-start + size, start + i * size, 0.0f));
		a->SetActorRotation(q);
	}

	// Setup lights
	renderer->SetAmbientLight(Vector3(0.2f, 0.2f, 0.2f));
	DirectionalLight& dir = renderer->GetDirectionalLight();
	dir.direction = Vector3(0.0f, -0.707f, -0.707f);
	dir.diffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	dir.specColor = Vector3(0.8f, 0.8f, 0.8f);
	
	// Camera actor
	Player* playerCamera = ECS->SpawnActor<Player>();

	// UI elements
	a = ECS->SpawnActor<Actor>();
	a->SetActorLocation(Vector3(-350.0f, -350.0f, 0.0f));
	SpriteRendererComponent* sc = new SpriteRendererComponent("../Solution/Assets/HealthBar.png", a);

	a = ECS->SpawnActor<Actor>();
	a->SetActorLocation(Vector3(375.0f, -275.0f, 0.0f));
	a->SetActorScale(Vector3(0.75f, 0.75f, 0.75f));
	sc = new SpriteRendererComponent("../Solution/Assets/Radar.png", a);

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
	SDL_Quit();
	std::cout << "Window Cleaned.\n";
}



bool Engine::IsRunning()
{
	return isRunning;
}


