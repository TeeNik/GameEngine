#pragma once
#include "ObjectSystem/Component.hpp"
#include "SDL.h"
#include "BaseStructs/Transform.hpp"
#include "ObjectSystem/Actor.hpp"
#include <string>

class Texture;

class SpriteRendererComponent : public Component {
	
public:
	SpriteRendererComponent(std::string, Actor* o, int drawOrder = 100);

	~SpriteRendererComponent();

	virtual void BeginPlay() override;
	virtual void SetTexture(std::string path);
	virtual void SetTexture(Texture* texture);
	virtual void Draw(class Shader* renderer);

	inline const int GetDrawOrder() const { return drawOrder; };
	inline const int GetTextureWidth() const { return textureWidth; };
	inline const int GetTextureHeight() const { return textureHeight; };

protected:
	Texture* texture;
	int drawOrder;
	int textureWidth;
	int textureHeight;
	const Transform* actorTransform;

	//SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

};