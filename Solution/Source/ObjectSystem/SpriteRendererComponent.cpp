#pragma once
#include "ObjectSystem/SpriteRendererComponent.hpp"
#include "SDL.h"
#include "Engine/Engine.hpp"
#include "Graphics/Renderer.hpp"
#include "Graphics/Shader.hpp"
#include "Graphics/Texture.hpp"

SpriteRendererComponent::SpriteRendererComponent(const char* path, Actor* o, int drawOrder) : Component(o), drawOrder(drawOrder)
{
	actorTransform = &owner->GetActorTransform();
	auto renderer = owner->GetEngine()->GetRenderer();
	renderer->AddSprite(this);
	texture = renderer->GetTexture(path);
	textureWidth = texture->GetWidth();
	textureHeight = texture->GetHeight();
}

SpriteRendererComponent::~SpriteRendererComponent()
{
	if (!texture)
	{
		texture->Unload();
	}
}

void SpriteRendererComponent::BeginPlay()
{
}

void SpriteRendererComponent::SetTexture(const char* path)
{
}

void SpriteRendererComponent::SetTexture(Texture* tex)
{
	texture = tex;
}

void SpriteRendererComponent::Draw(Shader* shader)
{
	Matrix4 scaleMat = Matrix4::CreateScale(textureWidth, textureHeight, 1);
	Matrix4 world = scaleMat * owner->GetWorldTransform();
	shader->SetMatrixUniform("uWorldTransform", world);
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