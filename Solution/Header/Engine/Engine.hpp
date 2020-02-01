#pragma once
#include "SDL.h"
#include "ObjectSystem\ObjectManager.hpp"
#include "Input\Input.hpp"

class Engine {

public:
	Engine();
	~Engine();

	void Init();
	void HandleEvents();
	void Update();
	void Render();
	void Clean();

	void Run();
	bool IsRunning();

private:
	ObjectManager ECS;
	Input Input;

	SDL_Window* window;
	SDL_Renderer* renderer;
	bool isRunning;
	int frameCounter = 0;

	const int FPS = 60;
	const int FrameDelay = 1000 / 60;
	int ticksCount;
	const float deltaTimeLimit = 0.05f;

	const int width = 1024;
	const int height = 720;

	//TODO refactor
	void InitWindow();

};