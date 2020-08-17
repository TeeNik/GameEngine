#pragma once
#include <string>
#include "Math/Math.h"

struct SDL_Surface;

class Texture {

public:
	Texture();
	~Texture();

	bool Load(const std::string& fileName);
	void Unload();
	void SetActive();
	void SetActive(int bindIndex);
	void CreateFromSurface(SDL_Surface* surface);

	inline const Vector2 GetSize() const { return size; }
	inline const int GetWidth() const { return width; }
	inline const int GetHeight() const { return height; }

private:
	unsigned int textureID;
	int width;
	int height;
	Vector2 size;
};