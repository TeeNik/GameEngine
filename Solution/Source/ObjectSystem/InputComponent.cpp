#include "ObjectSystem\InputComponent.hpp"
#include "Input\Input.hpp"

void InputComponent::BindKey(int keyCode, std::function<void()> func)
{
	Input::GetInputSubscriber()->Subscribe(keyCode, func);
}
