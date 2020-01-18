#pragma once
#include <vector>

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Rect;
class Component;

class Actor {

public:
	Actor(const char* filename, SDL_Renderer* renderer);
	~Actor();

	virtual void update();
	virtual void render();

	const bool IsActive();
	void Destroy();

private:

	std::vector<Component> components;
	
	bool isActive = true;

};