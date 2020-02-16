#include "Graphics\Graphics2D.hpp"
#include "ObjectSystem\SpriteRendererComponent.hpp"
#include "Graphics\Texture.hpp"

Graphics2D::Graphics2D(Shader* s, SDL_Renderer* r)
{
	shader = s;
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
		sprite->Draw(shader);
	}
}

Texture* Graphics2D::LoadTexture(const std::string& filename)
{
	Texture* texture = new Texture();
	texture->Load(filename);
	return texture;
}
