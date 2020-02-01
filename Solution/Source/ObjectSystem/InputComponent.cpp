#include "ObjectSystem\InputComponent.hpp"
#include "Input\Input.hpp"

InputComponent::InputComponent(Actor* a) : Component(a)
{
}

void InputComponent::BindKey(int keyCode, std::function<void()> func)
{
	Input::GetInputSubscriber()->Subscribe(keyCode, func);
}
