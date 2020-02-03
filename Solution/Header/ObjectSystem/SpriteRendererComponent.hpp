#pragma once
#include "ObjectSystem/Component.hpp"
#include "SDL.h"
#include "BaseStructs/Vector.hpp"

class SpriteRendererComponent : public Component {
	
private:
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
	const Transform& actorTransform;

public:
	SpriteRendererComponent(Actor* o);
	SpriteRendererComponent(const char* path, Actor* o);

	virtual void BeginPlay() override;
	virtual void Update(float deltaTime) override;
	void SetTexture(const char* path);
	virtual void Draw();
};