#pragma once
#include "Engine/Level.hpp"

class Engine;

class D3Level : public Level
{
public:
	D3Level(Engine* e);
	virtual void Load() override;
	virtual void Unload() override;
};