#pragma once

class Actor;

class Component
{
public:
	Component(Actor* o) : owner(o) {}
	Actor* GetOwner() { return owner; }

	virtual void BeginPlay() {}
	virtual void Update() {}

	virtual ~Component() {}

protected:
	Actor* owner;
};

