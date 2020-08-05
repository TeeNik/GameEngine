#include "Engine/Engine.hpp"
#include "Graphics/Renderer.hpp"
#include "Graphics/UI/Canvas.hpp"
#include "Graphics/Texture.hpp"
#include "Graphics/Shader.hpp"
#include "Utils/Utils.hpp"
#include "Graphics/UI/Text.hpp"
#include "Graphics/UI/Button.hpp"
#include "Input/InputSystem.hpp"

Canvas::Canvas(Engine* e) : engine(e)
{
	/*auto font = e->GetRenderer()->GetFont(Utils::ContructPath("Fonts/Ubuntu-Bold.ttf"));
	text = new Text(font);
	text->SetText("Some text", Color::LightPink);

	button = new Button("Button", "default.png", font, [](){
		printf("On Click\n");
	}, Vector2(0, 0), Vector2(100,50));

	uiElements.push_back(text);
	uiElements.push_back(button);*/
}

Canvas::~Canvas()
{
	for(auto element : uiElements)
	{
		delete element;
	}
}

void Canvas::ProcessInput()
{
	auto inputState = engine->GetInput()->GetState();
	auto mousePos = inputState.Mouse.GetPosition();

	mousePos.x -= engine->GetRenderer()->GetScreenWidth() / 2;
	mousePos.y = engine->GetRenderer()->GetScreenHeight() / 2 - mousePos.y;

	//if (button->ContainsPoint(mousePos)) {
	//	if (inputState.Mouse.GetButtonState(1) == ButtonState::Pressed) {
	//		button->OnClick();
	//	}
	//}
}

void Canvas::Update(float deltaTime)
{

}

void Canvas::Draw(Shader* shader)
{
	for (auto element : uiElements)
	{
		element->Draw(shader);
	}
}