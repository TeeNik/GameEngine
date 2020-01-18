#include "Engine/Actor.hpp"
#include "TextureManager.hpp"
#include "Engine/Component.hpp"
#include "SDL.h"

Actor::Actor(const char* filename, SDL_Renderer* rendr)
{

}

Actor::~Actor()
{

}

void Actor::update()
{
	for (auto& component : components) {
		component->Update();
	}
}

void Actor::render()
{
}

const bool Actor::IsActive()
{
	return false;
}

void Actor::Destroy()
{
}
