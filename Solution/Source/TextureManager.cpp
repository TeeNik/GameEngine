#pragma once
#include "TextureManager.hpp"
#include "SDL_image.h"

SDL_Renderer* TextureManager::renderer;

SDL_Texture* TextureManager::LoadTexture(const char * filename)
{
	SDL_Surface* tmpSurface = IMG_Load(filename);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	return texture;
}

void TextureManager::Draw(SDL_Texture* texture, const SDL_Rect& srcRect, const SDL_Rect& destRect)
{
	SDL_RenderCopy(renderer, texture, NULL, &destRect);
}

void TextureManager::SetRenderer(SDL_Renderer* r)
{
	renderer = r;
}
