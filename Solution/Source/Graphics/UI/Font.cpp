#include "Graphics/UI/Font.hpp"
#include "Graphics/Texture.hpp"

Font::Font(Engine* e) : engine(e)
{
}

Font::~Font()
{
}

bool Font::Load(const std::string& fileName)
{
	for (auto& size : fontSizes)
	{
		TTF_Font* font = TTF_OpenFont(fileName.c_str(), size);
		if (font == nullptr)
		{
			printf("Failed to load font %s in size %d\n", fileName.c_str(), size);
			printf("TTF_OpenFont: %s\n", TTF_GetError());
			return false;
		}
		fontData.emplace(size, font);
	}
	return true;
}

void Font::Unload()
{
	for (auto& font : fontData)
	{
		TTF_CloseFont(font.second);
	}
}

Texture* Font::RenderText(const std::string& text, const Vector3& color, int pointSize)
{
	Texture* texture = nullptr;

	SDL_Color sdlColor;
	sdlColor.r = static_cast<Uint8>(color.x * 255);
	sdlColor.g = static_cast<Uint8>(color.y * 255);
	sdlColor.b = static_cast<Uint8>(color.z * 255);
	sdlColor.a = 255;

	// Find the font data for this point size
	auto iter = fontData.find(pointSize);
	if (iter != fontData.end())
	{
		TTF_Font* font = iter->second;
		//const std::string& actualText = engine->GetText(textKey);
		SDL_Surface* surf = TTF_RenderUTF8_Blended(font, text.c_str(), sdlColor);
		if (surf != nullptr)
		{
			texture = new Texture();
			texture->CreateFromSurface(surf);
			SDL_FreeSurface(surf);
		}
	}
	else
	{
		SDL_Log("Point size %d is unsupported", pointSize);
	}

	return texture;
}
