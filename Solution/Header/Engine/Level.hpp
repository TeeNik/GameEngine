#pragma once

class Engine;

class Level
{
public:
	Level(Engine* e);
	virtual ~Level();

	virtual void Load();
	virtual void Unload();

protected:
	Engine* engine;
};