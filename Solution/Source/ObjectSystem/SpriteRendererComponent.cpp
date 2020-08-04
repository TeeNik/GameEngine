#pragma once
#include "ObjectSystem/SpriteRendererComponent.hpp"
#include "SDL.h"
#include "Engine/Engine.hpp"
#include "Graphics/Renderer.hpp"
#include "Graphics/Shader.hpp"
#include "Graphics/Texture.hpp"

SpriteRendererComponent::SpriteRendererComponent(Actor* o) : Component(o)
{
	updateOrder = 100;
	actorTransform = &owner->GetActorTransform();
	owner->GetEngine()->GetRenderer()->AddSprite(this);
}

SpriteRendererComponent::~SpriteRendererComponent()
{
	owner->GetEngine()->GetRenderer()->RemoveSprite(this);
	if (!texture)
	{
		texture->Unload();
	}
}
void SpriteRendererComponent::SetTexture(std::string path, int drawOrder)
{
	auto renderer = owner->GetEngine()->GetRenderer();
	texture = renderer->GetTexture(path);
	textureWidth = texture->GetWidth();
	textureHeight = texture->GetHeight();
}

//not finished
void SpriteRendererComponent::SetTexture(Texture* tex)
{
	texture = tex;
}

void SpriteRendererComponent::Draw(Shader* shader)
{
	Matrix4 scaleMat = Matrix4::CreateScale(textureWidth, textureHeight, 1);
	Matrix4 world = scaleMat * owner->GetWorldTransform();
	shader->SetMatrixUniform("uWorldTransform", world);
	
	shader->SetVectorUniform("uFrameMin", Vector3::Zero);
	shader->SetVectorUniform("uFrameMax", Vector3::One);

	texture->SetActive();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}