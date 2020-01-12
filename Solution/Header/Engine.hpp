struct SDL_Window;
struct SDL_Renderer;

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
	SDL_Window* window;
	SDL_Renderer* renderer;
	bool isRunning;

};