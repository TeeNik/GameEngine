#pragma once

struct SDL_Texture;
struct SDL_Renderer;

class TextureManager {

public:
	SDL_Texture* LoadTexture(const char* filename, SDL_Renderer* renderer);
};