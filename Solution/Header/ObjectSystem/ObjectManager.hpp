#pragma once
#include <vector>
#include <queue>
#include <memory>

class Actor;
class Engine;

class ObjectManager {

private:
	std::queue<std::shared_ptr<Actor>> pendingList;
	std::vector<std::shared_ptr<Actor>> objects;
	Engine* engine;

public:
	ObjectManager(Engine* e);
	~ObjectManager();

	void Update(float deltaTime);
	void Refresh();
	std::shared_ptr<Actor> CreateActor();
};

