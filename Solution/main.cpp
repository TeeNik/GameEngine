#include "Engine/Engine.hpp"
#include "vld.h"

int main(int argc, char* argv[])
{
	Engine* engine = new Engine;
	engine->Init();

	while (engine->IsRunning()) {
		engine->HandleEvents();
		engine->Update();
		engine->Render();
	}

	engine->Clean();
	delete engine;

	return 0;
}