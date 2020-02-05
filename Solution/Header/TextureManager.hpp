#pragma once

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Rect;

class TextureManager {

public:
	static SDL_Texture* LoadTexture(const char* filename);
	static void Draw(SDL_Texture* texture, const SDL_Rect& srcRect, const SDL_Rect& destRect);
	static void SetRenderer(SDL_Renderer* r);

private:
	static SDL_Renderer* renderer;
};