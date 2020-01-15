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
	int frameCounter = 0;

	const int FPS = 60;
	const int FrameDelay = 1000 / 60;

};