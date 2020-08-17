#pragma once
#include "ObjectSystem/Component.hpp"
#include <functional>

class LightComponent : public Component
{
public:
	LightComponent(Actor* o);

	virtual void ProcessLight() {};

};