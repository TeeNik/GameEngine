#pragma once
#include <vector>

class SpriteRendererComponent;
struct SDL_Texture;
struct SDL_Renderer;

class Graphics2D {

public:
	Graphics2D(SDL_Renderer* r);
	~Graphics2D();

	void AddSprite(SpriteRendererComponent* sr);
	void Draw();
	SDL_Texture* LoadTexture(const char* filename);

private:
	std::vector<SpriteRendererComponent*> sprites;
	SDL_Renderer* renderer;

};