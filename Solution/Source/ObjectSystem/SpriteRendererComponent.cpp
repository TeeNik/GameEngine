#pragma once
#include "ObjectSystem/SpriteRendererComponent.hpp"
#include "SDL.h"
#include "BaseStructs/Transform.hpp"
#include "ObjectSystem/Actor.hpp"
#include "TextureManager.hpp"
#include "Engine/Engine.hpp"
#include "Graphics/Graphics2D.hpp"

SpriteRendererComponent::SpriteRendererComponent(Actor* o, int drawOrder) : Component(o)
{
	Init();
}

SpriteRendererComponent::SpriteRendererComponent(const char* path, Actor* o, int drawOrder) : Component(o)
{
	Init();
	texture = TextureManager::LoadTexture(path);
	SDL_QueryTexture(texture, nullptr, nullptr, &texWidth, &texHeight);
}

void SpriteRendererComponent::BeginPlay()
{
	srcRect.x = srcRect.y = 0;
	srcRect.w = srcRect.h = 32;
	destRect.w = destRect.h = 64;
}

void SpriteRendererComponent::Init()
{
	actorTransform = &owner->GetActorTransform();
	owner->GetEngine()->GetGraphics2D()->AddSprite(this);
}


void SpriteRendererComponent::SetTexture(SDL_Texture* tex)
{
	texture = tex;
}

void SpriteRendererComponent::Draw(SDL_Renderer* renderer)
{
	if (texture) {
		auto& scale = actorTransform->scale;
		destRect.w = texWidth * scale.x;
		destRect.h = texWidth * scale.y;
		auto& pos = actorTransform->position;
		destRect.x = pos.x - destRect.w / 2;
		destRect.y = pos.y - destRect.h / 2;

		SDL_RenderCopyEx(renderer, texture, nullptr, &destRect, 0, nullptr, SDL_FLIP_NONE);
	}
}