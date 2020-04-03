#pragma once
#include <string>
#include "Math/Math.h"

class Texture;
class Shader;
class Font;

class Text {

public:
	Text(const Font* font);
	~Text();

	void SetText(const std::string& text, const Vector3& color = Color::White, int pointSize = 30);
	void SetColor(const Vector3& color);
	void SetPointSize(int size);

	inline Texture* GetTexture() { return texture; }

private:
	std::string text;
	int pointSize = 0;
	Vector3 color;
	Texture* texture = nullptr;
	const Font* font = nullptr;
};