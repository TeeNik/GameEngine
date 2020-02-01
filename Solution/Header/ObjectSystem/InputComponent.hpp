#pragma once
#include <functional>
#include "ObjectSystem/Component.hpp"

class Actor;

class InputComponent : public Component{

public:

	InputComponent(Actor*);
	void BindKey(int keyCode, std::function<void()> func);

};