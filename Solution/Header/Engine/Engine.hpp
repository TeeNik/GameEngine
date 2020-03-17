#pragma once
#include "SDL.h"

class InputSystem;
class Graphics2D;
class ObjectManager;
class InputSubscriber;
class Renderer;
class AudioSystem;

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

	//TODO Move systems' getters to interface
	//inline Graphics2D* GetGraphics2D() { return Graphics2DSystem; }
	inline InputSystem* GetInput() const { return inputSystem; }
	inline Renderer* GetRenderer() const { return renderer; }

private:
	ObjectManager* ECS;
	//Graphics2D* Graphics2DSystem;
	Renderer* renderer;
	AudioSystem* audioSystem;
	InputSystem* inputSystem;

	bool isRunning;
	int frameCounter = 0;

	const int FPS = 60;
	const int FrameDelay = 1000 / 60;
	int ticksCount;
	const float deltaTimeLimit = 0.05f;

	const int width = 1024;
	const int height = 720;
};