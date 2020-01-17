struct SDL_Window;
struct SDL_Renderer;
class TextureManager;

class Engine {

public:
	Engine();
	~Engine();

	void init();
	void handleEvents();
	void update();
	void render();
	void clean();

	void run();
	bool running();

private:
	TextureManager* textureManager;
	SDL_Window* window;
	SDL_Renderer* renderer;
	bool isRunning;
	int frameCounter = 0;

	const int FPS = 60;
	const int FrameDelay = 1000 / 60;

};