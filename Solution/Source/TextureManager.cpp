#include "../Header/TextureManager.hpp"
#include "SDL.h"
#include "SDL_image.h"

SDL_Texture* TextureManager::LoadTexture(const char * filename, SDL_Renderer * renderer)
{
	SDL_Surface* tmpSurface = IMG_Load(filename);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	return texture;
}
