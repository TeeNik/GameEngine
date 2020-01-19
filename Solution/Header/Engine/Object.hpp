#pragma once
#include <vector>
#include <bitset>
#include <algorithm>

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Rect;
class Component;

class Object {

public:
	Object();
	~Object();

	virtual void Update();
	virtual void Render();

	const bool IsActive();
	void Destroy();

	template<typename T>
	T* AddComponent();

private:

	const static std::size_t maxComponents = 32;
	std::vector<Component*> components;
	std::bitset<maxComponents> componentsBitSet;
	
	bool isActive = true;

};
