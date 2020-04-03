#include "Graphics/UI/Button.hpp"
#include "Graphics/Texture.hpp"
#include "Graphics/UI/Text.hpp"
#include "Graphics/UI/Font.hpp"

Button::Button(const std::string& buttonText, const std::string imageName, Font* font, std::function<void()> onClick,
	const Vector2& pos, const Vector2& dims) : mOnClick(onClick),
	mPosition(pos),
	dimensions(dims),
	mHighlighted(false)
{
	text = new Text(font);
	text->SetText(buttonText, Color::White, 30);

	image = new Texture();
	image->Load(imageName);
	dimensions = Vector2()
}

Button::~Button()
{
	delete text;
}

void Button::SetText(const std::string& buttonText)
{
	text->SetText(buttonText);
}

bool Button::ContainsPoint(const Vector2& pt) const
{
	bool no = pt.x < (mPosition.x - dimensions.x / 2.0f) ||
		pt.x >(mPosition.x + dimensions.x / 2.0f) ||
		pt.y < (mPosition.y - dimensions.y / 2.0f) ||
		pt.y >(mPosition.y + dimensions.y / 2.0f);
	return !no;
}

void Button::OnClick()
{
	if (mOnClick)
	{
		mOnClick();
	}
}
