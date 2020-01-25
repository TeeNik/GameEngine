#include "ObjectSystem/Actor.hpp"
#include "TextureManager.hpp"
#include "ObjectSystem/Component.hpp"
#include "SDL.h"

Actor::Actor()
{

}

Actor::~Actor()
{

}

void Actor::Update()
{
	for (auto& component : components) {
		component->Update();
	}
}

void Actor::Render()
{
}

const bool Actor::IsActive()
{
	return false;
}

template<typename T>
T* Actor::AddComponent()
{
	T* component = new T(this);
	components.push_back(component);
}


void Actor::Destroy()
{
	for(auto& c : components)
	{
		delete c;
	}
}
