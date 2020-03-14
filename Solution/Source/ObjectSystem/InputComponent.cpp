#include "ObjectSystem\InputComponent.hpp"
#include "Input\InputSystem.hpp"
#include "ObjectSystem\Actor.hpp"
#include "Engine\Engine.hpp"
#include "Input\InputSubscriber.hpp"

InputComponent::InputComponent(Actor* a) : Component(a)
{
}

void InputComponent::BindKey(int keyCode, std::function<void()> func)
{
	//owner->GetEngine()->GetInput()->Subscribe(keyCode, func);
}
