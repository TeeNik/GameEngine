#include "Header/Engine.hpp"

int main(int argc, char* argv[])
{
	Engine engine;
	engine.init();

	while (engine.running()) {
		engine.handleEvents();
		engine.update();
		engine.render();
	}

	engine.clean();

	return 0;
}