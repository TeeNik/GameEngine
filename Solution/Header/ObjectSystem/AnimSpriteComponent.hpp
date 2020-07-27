#pragma once
#include "ObjectSystem\SpriteRendererComponent.hpp"
#include <vector>

class AnimSpriteComponent : public SpriteRendererComponent {

public:

	AnimSpriteComponent(Actor* o) : SpriteRendererComponent(o) {};

	void SetSourceImage(const char* path, int col, int row, int drawOrder = 100);
	void Update(float deltaTime) override;
	//void Draw(SDL_Renderer* renderer) override;
	
	inline void SetAnimFPS(float fps) { animFPS = fps; }
	inline const float GetAnimFPS() { return animFPS; }

private:
	std::vector<int> frames{ 0, 1, 2, 3 };
	
	float currentFrame = 0;
	float animFPS = 4;
	int columns;
	int rows;
};