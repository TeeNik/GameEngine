#include "Engine\Actor.hpp"
#include "TextureManager.hpp"
#include "SDL.h"

Actor::Actor(const char * filename, SDL_Renderer * rendr)
{
	renderer = rendr;
	texture = TextureManager::LoadTexture(filename, renderer);
	scrRect = new SDL_Rect;
	destRect = new SDL_Rect;

	xPos = 0;
	yPos = 0;
}

Actor::~Actor()
{
	
}

void Actor::update()
{
	++xPos;
	++yPos;

	scrRect->h = 109;
	scrRect->w = 64;
	scrRect->x = 0;
	scrRect->y = 0;

	destRect->x = xPos;
	destRect->y = yPos;
	destRect->w = scrRect->w;
	destRect->h = scrRect->h;
}

void Actor::render()
{
	SDL_RenderCopy(renderer, texture, NULL, destRect);
}
