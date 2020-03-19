#pragma once
#include "Math/Math.h"
#include "SDL_mouse.h"

enum class ButtonState;

class MouseState {
	friend class InputSystem;

public:
	inline const Vector2& GetPosition() const { return mousePos; }
	inline const Vector2& GetScrollWheel() const { return scrollWheel; }
	inline bool IsRelative() const { return isRelative; }

	bool GetButtonValue(int button) const;
	ButtonState GetButtonState(int button) const;
private:
	Vector2 mousePos;
	Vector2 scrollWheel;
	Uint32 currButtons;
	Uint32 prevButtons;
	bool isRelative;
};
