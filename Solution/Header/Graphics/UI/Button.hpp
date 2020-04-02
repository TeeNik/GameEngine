#pragma once
#include <string>
#include <functional>
#include "Math/Math.h"

class Texture;
class Text;

class Button
{
public:
	Button(const std::string& name, class Font* font,
		std::function<void()> onClick,
		const Vector2& pos, const Vector2& dims);
	~Button();

	void SetName(const std::string& name);

	//class Texture* GetNameTex() { return mNameTex; }
	const Vector2& GetPosition() const { return mPosition; }
	void SetHighlighted(bool sel) { mHighlighted = sel; }
	bool GetHighlighted() const { return mHighlighted; }

	bool ContainsPoint(const Vector2& pt) const;
	void OnClick();
private:
	std::function<void()> mOnClick;
	class Texture* image;
	class Text* text;
	Vector2 mPosition;
	Vector2 mDimensions;
	bool mHighlighted;
};