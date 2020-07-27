#pragma once
#include <vector>
#include <queue>
#include <memory>

class Actor;
class Engine;

class ObjectManager {

private:
	std::queue<Actor*> pendingList;
	std::vector<Actor*> objects;

	Engine* engine;

public:
	ObjectManager(Engine * raw_e);
	~ObjectManager();

	void Update(float deltaTime);
	void Refresh();

	template<typename T>
	T* SpawnActor() {
		T* actor = new T(engine);
		pendingList.push(actor);
		return actor;
	}
};

