#include "ObjectSystem/ObjectManager.hpp"
#include "ObjectSystem/Actor.hpp"
#include <algorithm>

ObjectManager::ObjectManager(Engine * e)
{
	engine = e;
}

ObjectManager::~ObjectManager()
{
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
		[](std::shared_ptr<Actor> &object)
	{
		return !object->IsActive();
	}), std::end(objects));
}
 
std::shared_ptr<Actor> ObjectManager::CreateActor()
{
	std::shared_ptr<Actor> obj(new Actor(engine));
	pendingList.push(obj);
	return obj;
}


