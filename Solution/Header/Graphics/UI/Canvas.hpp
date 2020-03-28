#pragma once
#include "Math/Math.h"

class Shader;
class Texture;
class Text;
class Engine;

class Canvas {
public:
	Canvas(Engine* e);
	virtual ~Canvas();

	virtual void Update(float deltaTime);
	virtual void Draw(Shader* shader);

protected:
	void DrawTexture(Shader* shader, Texture* texture, const Vector2& offset = Vector2::Zero, float scale = 1.0f);

	Engine* engine;

private:
	Text* text;
};