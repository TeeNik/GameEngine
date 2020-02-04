#pragma once
#include "ObjectSystem/SpriteRendererComponent.hpp"
#include "ObjectSystem/Actor.hpp"
#include "TextureManager.hpp"

SpriteRendererComponent::SpriteRendererComponent(Actor* o) : Component(o), actorTransform(o->)
{
}

SpriteRendererComponent::SpriteRendererComponent(const char* path, Actor* o) : Component(o), actorTransform(o->GetActorLocation())
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
	destRect.x = actorTransform.Position.x;
	destRect.y = actorPosition.Position.y;
	TextureManager::Draw(texture, srcRect, destRect);
}

void SpriteRendererComponent::SetTexture(const char* path)
{
	texture = TextureManager::LoadTexture(path);
}

void SpriteRendererComponent::Draw()
{
	if (texture) {
		destRect.w = this->
	}
}
