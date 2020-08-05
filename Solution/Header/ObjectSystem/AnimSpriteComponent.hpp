#pragma once
#include "ObjectSystem\SpriteRendererComponent.hpp"
#include <vector>

class Shader;

class AnimSpriteComponent : public SpriteRendererComponent {

public:
	AnimSpriteComponent(Actor* o) : SpriteRendererComponent(o) {};

	void SetSourceImage(const std::string path, int col, int row, int drawOrder = 100);
	void Update(float deltaTime) override;
	void Draw(Shader* shader) override;
	
	inline void SetAnimFPS(float fps) { animFPS = fps; }
	inline const float GetAnimFPS() { return animFPS; }

private:
	std::vector<std::pair<int, int>> frames{ std::pair<int, int> {36, 43} };
	
	float currentFrame = 0;
	float animFPS = 4;
	int columns;
	int rows;
};