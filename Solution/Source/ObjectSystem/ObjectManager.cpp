#include "ObjectSystem/ObjectManager.hpp"
#include "ObjectSystem/Actor.hpp"
#include <algorithm>

ObjectManager::ObjectManager(Engine * e)
{
	engine = e;
}

ObjectManager::~ObjectManager()
{
	for (auto actor : objects)
	{
		delete actor;
	}
}

void ObjectManager::Update(float deltaTime)
{
	while (!pendingList.empty()) {
		auto actor = pendingList.front();
		actor->BeginPlay();
		pendingList.pop();
		objects.push_back(actor);
	}

	for (auto obj : objects) {
		obj->Update(deltaTime);
	}
}

void ObjectManager::Refresh()
{
	objects.erase(std::remove_if(std::begin(objects), std::end(objects), 
		[](Actor* &object)
	{
		return !object->IsActive();
	}), std::end(objects));
}
 
Actor* ObjectManager::CreateActor()
{
	auto actor = new Actor(engine);
	pendingList.push(actor);
	return actor;
}


