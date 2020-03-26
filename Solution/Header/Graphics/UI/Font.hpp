#pragma once
#include <string>
#include <unordered_map>
#include <SDL_ttf.h>
#include "Math/Math.h"

class Texture;
class Engine;

class Font {
public:
	Font(Engine* e);
	~Font();

	bool Load(const std::string& fileName);
	void Unload();

	Texture* RenderText(const std::string& textKey, const Vector3& color = Color::White, int pointSize = 30);

private:
	std::unordered_map<int, TTF_Font*> fontData;
	Engine* engine;

	const std::vector<int> fontSizes = {
		8,  9,  10, 11, 12, 14, 16,
		18,	20, 22, 24, 26, 28, 30,
		32, 34,	36, 38,	40, 42, 44,
		46, 48,	52,	56,	60, 64, 68,	72
	};
};