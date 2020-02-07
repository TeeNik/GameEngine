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
	ObjectManager(Engine* e);
	~ObjectManager();

	void Update(float deltaTime);
	void Refresh();
	Actor* CreateActor();
};

