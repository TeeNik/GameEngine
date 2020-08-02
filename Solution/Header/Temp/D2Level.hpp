#pragma once
#include "Engine/Level.hpp"

class Engine;

class D2Level : public Level 
{
public:
	D2Level(Engine* e);
	virtual void Load() override;
	virtual void Unload() override;

};