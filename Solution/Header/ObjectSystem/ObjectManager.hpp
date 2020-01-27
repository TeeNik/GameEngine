#pragma once
#include <vector>
#include <queue>

class Actor;

class ObjectManager {

private:
	std::queue<Actor*> beginPlayList;
	std::vector<Actor*> objects;

public:

	void Update();
	void Refresh();
	Actor* CreateActor();
};

