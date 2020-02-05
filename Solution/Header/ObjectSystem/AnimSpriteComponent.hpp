#pragma once
#include "ObjectSystem\SpriteRendererComponent.hpp"
#include <vector>

class AnimSpriteComponent : public SpriteRendererComponent {

	AnimSpriteComponent(const char* path, Actor* o, int drawOrder = 100);

	void Update(float deltaTime) override;
	

};