#pragma once
#include <string>
#include <functional>
#include "Math/Math.h"
#include "Graphics/UI/UIElement.hpp"

class Texture;
class Text;
class Font;

class Button : public UIElement
{
public:
	Button(const std::string& buttonText, const std::string& imageName, const Font* font,
		std::function<void()> onClick,
		const Vector2& pos, const Vector2& dims);
	~Button();

	void SetText(const std::string& name);

	//class Texture* GetNameTex() { return mNameTex; }
	const Vector2& GetPosition() const { return position; }
	void SetHighlighted(bool sel) { highlighted = sel; }
	bool GetHighlighted() const { return highlighted; }

	bool ContainsPoint(const Vector2& pt) const;
	void OnClick();

	virtual void Draw(Shader* shader) override;
private:
	std::function<void()> onClick;
	Texture* image;
	Text* text;
	Vector2 position;
	Vector2 dimensions;
	bool highlighted;
};