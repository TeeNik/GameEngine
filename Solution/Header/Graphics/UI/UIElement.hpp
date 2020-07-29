#pragma once

class Shader;
class Texture;
class Vector2;

class UIElement
{

public:
	virtual void Draw(Shader* shader) = 0;
	virtual ~UIElement() {};

protected:
	void DrawTexture(Shader* shader, Texture* texture, const Vector2& size, const Vector2& position, float scale);
};
