#pragma once
#include <vector>

class SpriteRendererComponent;
struct SDL_Texture;
struct SDL_Renderer;
class Shader;

class Graphics2D {

public:
	Graphics2D(Shader* s, SDL_Renderer* renderer);
	~Graphics2D();

	void AddSprite(SpriteRendererComponent* sr);
	void Draw();
	SDL_Texture* LoadTexture(const char* filename);

private:
	std::vector<SpriteRendererComponent*> sprites;
	Shader* shader;
	SDL_Renderer* renderer;

};