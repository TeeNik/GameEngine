#pragma once
#include "ObjectSystem/SpriteRendererComponent.hpp"
#include "ObjectSystem/Actor.hpp"
#include "TextureManager.hpp"

SpriteRendererComponent::SpriteRendererComponent(Actor* o) : Component(o), actorPosition(o->GetActorLocation())
{
}

SpriteRendererComponent::SpriteRendererComponent(const char* path, Actor* o) : Component(o), actorPosition(o->GetActorLocation())
{
	texture = TextureManager::LoadTexture(path);
}

void SpriteRendererComponent::BeginPlay()
{
	srcRect.x = srcRect.y = 0;
	srcRect.w = srcRect.h = 32;
	destRect.w = destRect.h = 64;
}

void SpriteRendererComponent::Update(float deltaTime)
{
	destRect.x = actorPosition.x;
	destRect.y = actorPosition.y;
	TextureManager::Draw(texture, srcRect, destRect);
}

void SpriteRendererComponent::SetTexture(const char* path)
{
	texture = TextureManager::LoadTexture(path);
}

void SpriteRendererComponent::Draw()
{
	if (texture) {

	}
}
