#include "ObjectSystem/ObjectManager.hpp"
#include "ObjectSystem/Actor.hpp"
#include <algorithm>

ObjectManager::ObjectManager(Engine * e)
{
	engine = e;
}

ObjectManager::~ObjectManager()
{
	while (!pendingList.empty()) {
		auto actor = pendingList.front();
		delete actor;
		pendingList.pop();
	}
	for (auto actor : objects) {
		delete actor;
	}
	objects.clear();
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
	for (auto& obj : objects) {
		if (!obj->IsActive()) {
			delete obj;
			obj = nullptr;
		}
	}

	objects.erase(std::remove_if(std::begin(objects), std::end(objects), 
		[](Actor* &object)
	{
		return object == nullptr;
	}), std::end(objects));
}
 
Actor* ObjectManager::CreateActor()
{
	Actor* obj = new Actor(engine);
	pendingList.push(obj);
	return obj;
}


