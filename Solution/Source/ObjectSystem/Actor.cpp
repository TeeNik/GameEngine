#include "ObjectSystem/Actor.hpp"
#include "ObjectSystem/Component.hpp"
#include "SDL.h"
#include "Engine/Engine.hpp"

Actor::Actor(Engine* e)
{
	engine = e;
}

Actor::~Actor()
{
	for (auto& c : components)
	{
		delete c;
	}
}

void Actor::BeginPlay()
{
	for (auto comp : components) {
		comp->BeginPlay();
	}
}

void Actor::Update(float deltaTime)
{
	ComputeWorldTransform();

	for (auto& component : components) {
		component->Update(deltaTime);
	}
}

void Actor::Render()
{
}

const bool Actor::IsActive()
{
	return false;
}

void Actor::Destroy()
{
	isActive = false;
}

void Actor::AddComponent(Component * component)
{
	int myOrder = component->GetUpdateOrder();
	auto iter = components.begin();
	for (;
		iter != components.end();
		++iter)
	{
		if (myOrder < (*iter)->GetUpdateOrder())
		{
			break;
		}
	}
	components.insert(iter, component);
}

void Actor::RemoveComponent(Component * component)
{
	auto iter = std::find(components.begin(), components.end(), component);
	if (iter != components.end())
	{
		components.erase(iter);
	}
}

void Actor::ComputeWorldTransform()
{
	if (recomputeWorldTransform) {
		recomputeWorldTransform = false;

		worldTransform = Matrix4::CreateScale(transform.scale);
		worldTransform *= Matrix4::CreateFromQuaternion(transform.rotation);
		worldTransform *= Matrix4::CreateTranslation(transform.position);
	}
}
