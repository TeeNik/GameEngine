#pragma once
#include "Math/Math.h"

class Shader;
class Texture;
class Text;
class Button;
class Engine;
class UIElement;

class Canvas {
public:
	Canvas(Engine* e);
	virtual ~Canvas();

	virtual void ProcessInput();
	virtual void Update(float deltaTime);
	virtual void Draw(Shader* shader);

private:
	Engine* engine;
	Text* text;
	Button* button;

	std::vector<UIElement*> uiElements;
};