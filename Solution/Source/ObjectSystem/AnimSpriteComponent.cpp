#include "ObjectSystem\AnimSpriteComponent.hpp"

AnimSpriteComponent::AnimSpriteComponent(const char* path, int col, int row, Actor* o, int drawOrder) : SpriteRendererComponent(path, o, drawOrder)
{
	columns = col;
	rows = row;

	srcRect.w = textureWidth / columns;
	srcRect.h = textureHeight / rows;
}

void AnimSpriteComponent::Update(float deltaTime)
{
	SpriteRendererComponent::Update(deltaTime);

	currentFrame += (animFPS * deltaTime);
	while (currentFrame >= frames.size()) {
		currentFrame -= frames.size();
	}
	//currentFrame = static_cast<int>(currentFrame) % frames.size();
}

/*void AnimSpriteComponent::Draw(SDL_Renderer* renderer)
{
	if (texture) {
		auto& scale = actorTransform->scale;
		destRect.w = srcRect.w * scale.x;
		destRect.h = srcRect.h * scale.y;
		auto& pos = actorTransform->position;
		destRect.x = pos.x - destRect.w / 2;
		destRect.y = pos.y - destRect.h / 2;

		int frame = frames[static_cast<int>(currentFrame)];
		srcRect.x = (frame % columns) * srcRect.w;
		srcRect.y = (frame / rows) * srcRect.h;

		SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect, 0, nullptr, SDL_FLIP_NONE);
	}
}*/
