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

SpriteRendererComponent::~SpriteRendererComponent()
{
	if (!texture)
	{
		SDL_DestroyTexture(texture);
	}
}

void SpriteRendererComponent::BeginPlay()
{
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
		destRect.w = texWidth * scale.x / 7;
		destRect.h = texHeight * scale.y / 11;
		auto& pos = actorTransform->position;
		destRect.x = pos.x - destRect.w / 2;
		destRect.y = pos.y - destRect.h / 2;

		srcRect.h = 37;
		srcRect.w = 50;
		srcRect.x = srcRect.y = 0;

		SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect, 0, nullptr, SDL_FLIP_NONE);
	}
}