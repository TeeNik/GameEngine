#include "Graphics/UI/Text.hpp"
#include "Engine/Engine.hpp"
#include "Graphics/Renderer.hpp"
#include "Graphics/UI/Font.hpp"
#include "Graphics/Texture.hpp"

Text::Text(const Font* f) : font(f)
{
}

Text::~Text()
{
	if (texture != nullptr) {
		texture->Unload();
		delete texture;
	}
}

void Text::SetText(const std::string& t, const Vector3& c, int s)
{
	if (text != t && color != c && pointSize != s) {
		text = t;
		color = c;
		pointSize = s;
		texture = font->RenderText(text, color, pointSize);
	}
}

void Text::SetColor(const Vector3& c)
{
	if (color != c) {
		color = c;
		texture = font->RenderText(text, color, pointSize);
	}
}

void Text::SetPointSize(int s)
{
	if (pointSize != s) {
		pointSize = s;
		texture = font->RenderText(text, color, pointSize);
	}
}