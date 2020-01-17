#include "Header/Engine.hpp"

int main(int argc, char* argv[])
{
	Engine* engine = new Engine;
	engine->init();

	while (engine->running()) {
		engine->handleEvents();
		engine->update();
		engine->render();
	}

	engine->clean();
	delete engine;

	return 0;
}