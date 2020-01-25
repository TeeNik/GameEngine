#include "ObjectSystem/ObjectManager.hpp"
#include "ObjectSystem/Actor.hpp"
#include <algorithm>

void ObjectManager::Update()
{
	for (auto obj : objects) {
		obj->Update();
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
	Actor* obj = new Actor;
	objects.push_back(obj);
	return obj;
}


