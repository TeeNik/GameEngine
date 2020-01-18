#pragma once

class Actor;

class Component
{
public:

	Actor* GetOwner() { return owner; }

	virtual void BeginPlay() {}
	virtual void Update() {}

	virtual ~Component() {}
	
private:
	Actor* owner;
};

