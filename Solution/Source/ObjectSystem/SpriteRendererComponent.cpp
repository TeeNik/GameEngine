#pragma once
#include "ObjectSystem/SpriteRendererComponent.hpp"
#include "ObjectSystem/Actor.hpp"
#include "TextureManager.hpp"
#include "Engine/Engine.hpp"
#include "Graphics/Graphics2D.hpp"

SpriteRendererComponent::SpriteRendererComponent(Actor* o, int drawOrder) : Component(o)
{
}

SpriteRendererComponent::SpriteRendererComponent(const char* path, Actor* o, int drawOrder) : Component(o)
{
	texture = TextureManager::LoadTexture(path);
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

void SpriteRendererComponent::Draw()
{
	if (texture) {
		destRect.w = this->
	}
}