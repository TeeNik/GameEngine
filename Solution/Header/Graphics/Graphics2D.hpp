#pragma once
#include <vector>
#include <string>

class SpriteRendererComponent;
class Texture;
struct SDL_Renderer;
class Shader;

class Graphics2D {

public:
	Graphics2D(Shader* s, SDL_Renderer* renderer);
	~Graphics2D();

	void AddSprite(SpriteRendererComponent* sr);
	void Draw();
	Texture* LoadTexture(const std::string& filename);

private:
	std::vector<SpriteRendererComponent*> sprites;
	Shader* shader;
	SDL_Renderer* renderer;

};