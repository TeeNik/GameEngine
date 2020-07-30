#pragma once
#include "ObjectSystem/Component.hpp"
#include "Physics/Collision.hpp"
class Actor;

class BoxComponent : public Component
{
public:
	BoxComponent(Actor* owner);

	virtual void Update(float deltaTime) override;

	inline void SetObjectBox(const AABB& model) { objectBox = model; }
	inline const AABB& GetWorldBox() const { return worldBox; }
private:
	AABB objectBox;
	AABB worldBox;
	bool shouldRotate;
};
