#pragma once
#include "ObjectSystem/SpriteRendererComponent.hpp"
#include "SDL.h"
#include "Engine/Engine.hpp"
#include "Graphics/Graphics2D.hpp"
#include "Graphics/Shader.hpp"

SpriteRendererComponent::SpriteRendererComponent(const char* path, Actor* o, int drawOrder) : Component(o)
{
	actorTransform = &owner->GetActorTransform();
	auto graphics = owner->GetEngine()->GetGraphics2D();
	graphics->AddSprite(this);
	texture = graphics->LoadTexture(path);
	SDL_QueryTexture(texture, nullptr, nullptr, &textureWidth, &textureHeight);
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

void SpriteRendererComponent::SetTexture(const char* path)
{
}

void SpriteRendererComponent::SetTexture(SDL_Texture* tex)
{
	texture = tex;
}

void SpriteRendererComponent::Draw(Shader* renderer)
{
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	/*if (texture) {
		auto& scale = actorTransform->scale;
		destRect.w = textureWidth * scale.x;
		destRect.h = textureHeight * scale.y;
		auto& pos = actorTransform->position;
		destRect.x = pos.x - destRect.w / 2;
		destRect.y = pos.y - destRect.h / 2;

		SDL_RenderCopyEx(renderer, texture, nullptr, &destRect, 0, nullptr, SDL_FLIP_NONE);
	}*/
}