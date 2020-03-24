#pragma once
#include <string>

struct SDL_Surface;

class Texture {

public:
	Texture();
	~Texture();

	bool Load(const std::string& fileName);
	void Unload();
	void SetActive();
	void CreateFromSurface(SDL_Surface* surface);

	inline const int GetWidth() const { return width; }
	inline const int GetHeight() const { return height; }

private:
	unsigned int textureID;
	int width;
	int height;
};