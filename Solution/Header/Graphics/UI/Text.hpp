#pragma once
#include <string>
#include "Math/Math.h"
#include "Graphics/UI/UIElement.hpp"

class Texture;
class Shader;
class Font;

class Text : public UIElement {

public:
	Text(const Font* font);
	~Text();

	void SetText(const std::string& text, const Vector3& color = Color::White, int pointSize = 30);
	void SetColor(const Vector3& color);
	void SetPointSize(int size);
	
	inline void SetPosition(const Vector2& pos) { position = pos; }
	inline Texture* GetTexture() { return texture; }

	virtual void Draw(Shader* shader) override;

private:
	Vector2 position;
	std::string text;
	int pointSize = 0;
	Vector3 color;
	Texture* texture = nullptr;
	const Font* font = nullptr;
};