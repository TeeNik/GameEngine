#pragma once
#include <vector>
#include <bitset>
#include <algorithm>
#include "BaseStructs/Transform.hpp"

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Rect;
class Component;

class Actor {

public:
	Actor();
	~Actor();

	virtual void Update();
	virtual void Render();

	const bool IsActive();
	void Destroy();

	template<typename T>
	T* AddComponent();

	inline Vector& GetActorLocation() { return Transform.Position; }

protected:

	const static std::size_t maxComponents = 32;
	std::vector<Component*> components;
	std::bitset<maxComponents> componentsBitSet;
	Transform Transform;

	bool isActive = true;

};
