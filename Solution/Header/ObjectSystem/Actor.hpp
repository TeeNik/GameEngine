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

	template<typename T>
	T* AddComponent() {
		T* component = new T(this);
		int order = component->GetUpdateOrder();
		auto iter = components.begin();
		for (; iter != components.end(); ++iter)
		{
			if (order < (*iter)->GetUpdateOrder())
			{
				break;
			}
		}
		components.insert(iter, component);
		return component;
	}

	//void AddComponent(Component* component);
	void RemoveComponent(Component* component);
	
	inline Engine * GetEngine() { return engine; }
	inline const Matrix4 GetWorldTransform() { return worldTransform; }
	inline const Transform& GetActorTransform() { return transform; }
	
	inline const Vector3& GetActorPosition() { return transform.position;}
	inline void SetActorPosition(const Vector3& location) { transform.position = location; recomputeWorldTransform = true;}
	
	inline const Vector3& GetActorScale() { return transform.scale; }
	inline void SetActorScale(const Vector3& scale) { transform.scale = scale; recomputeWorldTransform = true; }
	
	inline const Quaternion& GetActorRotation() { return transform.rotation; }
	inline void SetActorRotation(const Quaternion& rotation) { transform.rotation = rotation; recomputeWorldTransform = true; }
	
	inline Vector3 GetForward() const { return Vector3::Transform(Vector3::UnitX, transform.rotation); }
	inline Vector3 GetRight() const { return Vector3::Transform(Vector3::UnitY, transform.rotation); }
	inline Vector3 GetUp() const { return Vector3::Transform(Vector3::UnitZ, transform.rotation); }

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

