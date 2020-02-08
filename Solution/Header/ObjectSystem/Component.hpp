#pragma once

class Actor;

class Component
{
public:
	Component(Actor* o, int updateOrd = 100);
	Actor* GetOwner() { return owner; }

	virtual void BeginPlay() {}
	virtual void Update(float deltaTime) {}
	inline int GetUpdateOrder() const { return updateOrder; };

	virtual ~Component() {}

protected:
	Actor* owner;
	int updateOrder;
};

