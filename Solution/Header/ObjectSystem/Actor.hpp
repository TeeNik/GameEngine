#pragma once
#include <vector>
#include <bitset>
#include <algorithm>
#include "BaseStructs/Transform.hpp"

class Component;
class Engine;

class Actor {
public:
	Actor(Engine* engine);
	virtual ~Actor();

	virtual void BeginPlay();
	virtual void Update(float deltaTime);

	virtual void Render();

	const bool IsActive();
	void Destroy();

	template<typename T, typename... TArgs>
	T* AddComponent(TArgs&&... args)
	{
		T* comp = new T(std::forward<TArgs>(args)..., this);
		components.push_back(comp);
		return comp;
	}

	/*void AddComponent(Component* component);
	void RemoveComponent(Component* component);*/
	
	inline Engine *const GetEngine() { return engine; }
	inline const Transform& GetActorTransform() { return transform; }
	inline const Vector& GetActorLocation() { return transform.position; }
	inline void SetActorLocation(Vector& vector) { transform.position = vector; }

protected:

	std::vector<Component*> components;
	Transform transform;
	bool isActive = true;
	
private:
	Engine* engine;

};

