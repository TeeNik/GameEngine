#pragma once
#include "ObjectSystem/Component.hpp"
#include "Physics/Collision.hpp"
class Actor;

enum CollisionObjectType
{
	Static,
	Dynamic,
};

class BoxComponent : public Component
{
public:
	BoxComponent(Actor* owner);
	virtual ~BoxComponent();

	virtual void Update(float deltaTime) override;

	inline void SetObjectBox(const AABB& model) { objectBox = model; }
	inline const AABB& GetWorldBox() const { return worldBox; }

	inline const CollisionObjectType GetObjectType() const { return objectType; }
	inline void SetObjectType(const CollisionObjectType type) { objectType = type; }

	Vector3 NextPos;
	AABB GetNextBox() {
		AABB next = objectBox;
		next.min += NextPos;
		next.max += NextPos;
		return next;
	};

private:
	CollisionObjectType objectType;
	AABB objectBox;
	AABB worldBox;
	bool shouldRotate;
};
