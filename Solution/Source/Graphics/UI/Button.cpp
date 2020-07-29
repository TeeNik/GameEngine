#include "Graphics/UI/Button.hpp"
#include "Graphics/Texture.hpp"
#include "Graphics/UI/Text.hpp"
#include "Graphics/UI/Font.hpp"
#include "Utils/Utils.hpp"

Button::Button(const std::string& buttonText, const std::string& imageName, 
		const Font* font, std::function<void()> onClick,
		const Vector2& pos, const Vector2& dims) : onClick(onClick),
		position(pos), dimensions(dims), highlighted(false)
{
	text = new Text(font);
	text->SetText(buttonText, Color::White, 30);

	image = new Texture();
	image->Load(Utils::ContructPath(imageName));
	dimensions = dims;
}

Button::~Button()
{
	delete text;
	delete image;
}

void Button::SetText(const std::string& buttonText)
{
	text->SetText(buttonText);
}

bool Button::ContainsPoint(const Vector2& pt) const
{
	bool no = pt.x < (position.x - dimensions.x / 2.0f) ||
		pt.x >(position.x + dimensions.x / 2.0f) ||
		pt.y < (position.y - dimensions.y / 2.0f) ||
		pt.y >(position.y + dimensions.y / 2.0f);
	return !no;
}

void Button::OnClick()
{
	if (onClick)
	{
		onClick();
	}
}

void Button::Draw(Shader* shader)
{
	DrawTexture(shader, image, dimensions, position, 1);
	DrawTexture(shader, text->GetTexture(), dimensions, position, 1);
}
