#pragma once
#include "ObjectSystem/Component.hpp"
#include "SDL.h"
#include "BaseStructs/Transform.hpp"
#include "ObjectSystem/Actor.hpp"

class SpriteRendererComponent : public Component {
	
public:
	SpriteRendererComponent(const char* path, Actor* o, int drawOrder = 100);

	~SpriteRendererComponent();

	virtual void BeginPlay() override;
	virtual void SetTexture(const char* path);
	virtual void SetTexture(SDL_Texture* texture);
	virtual void Draw(SDL_Renderer* renderer);

	inline const int GetDrawOrder() const { return drawOrder; };
	inline const int GetTextureWidth() const { return textureWidth; };
	inline const int GetTextureHeight() const { return textureHeight; };

protected:

	int drawOrder;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
	const Transform*  actorTransform;
	int textureWidth;
	int textureHeight;

};