#include "Engine/Object.hpp"
#include "TextureManager.hpp"
#include "Engine/Component.hpp"
#include "SDL.h"

Object::Object()
{

}

Object::~Object()
{

}

void Object::Update()
{
	for (auto& component : components) {
		component->Update();
	}
}

void Object::Render()
{
}

const bool Object::IsActive()
{
	return false;
}

template<typename T>
T* Object::AddComponent()
{
	T* component = new T;
	
}


void Object::Destroy()
{
	for(auto& c : components)
	{
		delete c;
	}
}
