class SDL_Window;
class SDL_Renderer;

class Engine {

public:
	Engine();
	~Engine();

	void init();
	void handleEvents();
	void update();
	void render();
	void clean();

	bool running();

private:
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;

};