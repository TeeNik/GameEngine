#pragma once

class Object;

class Component
{
public:
	Component(Object* o) : owner(o) {}
	Object* GetOwner() { return owner; }

	virtual void BeginPlay() {}
	virtual void Update() {}

	virtual ~Component() {}

private:
	Object* owner;
};

