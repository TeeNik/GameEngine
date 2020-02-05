#include "Graphics\Graphics2D.hpp"
#include "ObjectSystem\SpriteRendererComponent.hpp"
#include "SDL_image.h"

Graphics2D::Graphics2D(SDL_Renderer* r)
{
	renderer = r;
}

Graphics2D::~Graphics2D()
{
}

void Graphics2D::AddSprite(SpriteRendererComponent* sr)
{
	int drawOrder = sr->GetDrawOrder();
	auto iter = sprites.begin();
	for (; iter != sprites.end(); ++iter) {
		if (drawOrder < (*iter)->GetDrawOrder()) {
			break;
		}
	}
	sprites.insert(iter, sr);
}

void Graphics2D::Draw()
{
	for (auto sprite : sprites) {
		sprite->Draw(renderer);
	}
}

SDL_Texture* Graphics2D::LoadTexture(const char* filename)
{
	SDL_Surface* tmpSurface = IMG_Load(filename);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	return texture;
}
