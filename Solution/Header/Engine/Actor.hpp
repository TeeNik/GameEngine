#pragma once

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Rect;

class Actor {
	
public:
	Actor(const char * filename, SDL_Renderer * renderer);
	~Actor();

	void update();
	void render();
private:
	
	int xPos;
	int yPos;

	SDL_Texture* texture;
	SDL_Rect* scrRect;
	SDL_Rect* destRect;
	SDL_Renderer* renderer;

};