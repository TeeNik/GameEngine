#pragma once
#include <vector>
#include <bitset>
#include <algorithm>
#include "BaseStructs/Transform.hpp"

class Component;

class Actor {

public:
	Actor();
	~Actor();

	virtual void Update();
	virtual void Render();

	const bool IsActive();
	void Destroy();

	template<typename T, typename... TArgs>
	T* AddComponent(TArgs&&... args)
	{
		T* comp = new T(std::forward<TArgs>(args)...);
		components.push_back(comp);
		return comp;
	}

	inline Vector& GetActorLocation() { return Transform.Position; }

protected:

	const static std::size_t maxComponents = 32;
	std::vector<Component*> components;
	std::bitset<maxComponents> componentsBitSet;
	Transform Transform;

	bool isActive = true;

};

