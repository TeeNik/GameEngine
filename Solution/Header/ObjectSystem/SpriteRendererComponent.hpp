#pragma once
#include "ObjectSystem/Component.hpp"
#include "SDL.h"
#include "BaseStructs/Transform.hpp"
#include "ObjectSystem/Actor.hpp"
#include <string>
#include "Math/Math.h"

class Texture;

class SpriteRendererComponent : public Component {
	
public:
	SpriteRendererComponent(Actor* o);
	~SpriteRendererComponent();

	virtual void SetTexture(std::string path, int drawOrder = 100);
	virtual void SetTexture(Texture* texture);
	void SetSize(const Vector2& s) { size = s; };
	virtual void Draw(class Shader* renderer);

	inline const int GetDrawOrder() const { return drawOrder; };
	//inline const int GetTextureWidth() const { return textureWidth; };
	//inline const int GetTextureHeight() const { return textureHeight; };
	inline const Vector2& GetSize() const { return size; };
	inline const Vector2& GetTextureSize() const { return size; };

protected:
	Vector2 size;
	Vector2 textureSize;
	Texture* texture;
	int drawOrder;
	//int textureWidth;
	//int textureHeight;
	const Transform* actorTransform;
};