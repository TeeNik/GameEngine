#pragma once
#include <vector>
#include <bitset>
#include <algorithm>
#include "BaseStructs/Transform.hpp"
#include "Math/Math.h"

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

	void AddComponent(Component* component);
	void RemoveComponent(Component* component);
	
	inline Engine *const GetEngine() { return engine; }
	inline const Matrix4 GetWorldTransform() { return worldTransform; }
	inline const Transform& GetActorTransform() { return transform; }
	
	inline const Vector3& GetActorLocation() { return transform.position;}
	inline void SetActorLocation(const Vector3& location) { transform.position = location; recomputeWorldTransform = true;}
	
	inline const Vector3& GetActorScale() { return transform.scale; }
	inline void SetActorScale(const Vector3& scale) { transform.scale = scale; recomputeWorldTransform = true; }
	
	inline const Vector3& GetActorRotation() { return transform.rotation; }
	inline void SetActorRotation(const Vector3& rotation) { transform.rotation = rotation; recomputeWorldTransform = true; }
	
	void ComputeWorldTransform();

protected:

	std::vector<Component*> components;
	Transform transform;
	bool isActive = true;
	
	Matrix4 worldTransform;
	bool recomputeWorldTransform;

private:
	Engine* engine;

};

