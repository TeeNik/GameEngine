#pragma once
#include <vector>

class Actor;

class ObjectManager {

private:
	std::vector<Actor*> objects;

public:

	void Update();
	void Refresh();
	Actor* CreateActor();
};

