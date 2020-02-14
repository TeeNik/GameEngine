#include "Graphics\Graphics2D.hpp"
#include "ObjectSystem\SpriteRendererComponent.hpp"
#include "SDL_image.h"

Graphics2D::Graphics2D(Shader* s)
{
	shader = s;
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
		sprite->Draw(shader);
	}
}

SDL_Texture* Graphics2D::LoadTexture(const char* filename)
{
	return nullptr;

	SDL_Surface* tmpSurface = IMG_Load(filename);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	return texture;
}
