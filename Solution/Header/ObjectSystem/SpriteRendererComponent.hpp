#pragma once
#include "ObjectSystem/Component.hpp"
#include "SDL.h"

class Actor;
struct SDL_Texture;
struct SDL_Rect;
struct Transform;
class Component;

class SpriteRendererComponent : public Component {
	
public:
	SpriteRendererComponent(Actor* o, int drawOrder = 100);
	SpriteRendererComponent(const char* path, Actor* o, int drawOrder = 100);

	~SpriteRendererComponent();

	virtual void BeginPlay() override;
	//void SetTexture(const char* path);
	virtual void SetTexture(SDL_Texture* texture);
	virtual void Draw(SDL_Renderer* renderer);

	inline int GetDrawOrder() const { return drawOrder; };
	inline int GetTexWidth() const { return texWidth; }
	inline int GetTexHeight() const { return texHeight; }

protected:
	void Init();

	int drawOrder;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
	const Transform*  actorTransform;
	int texWidth;
	int texHeight;

};