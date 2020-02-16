#pragma once
#include <string>

class Texture {

public:
	Texture();
	~Texture();

	bool Load(const std::string& fileName);
	void Unload();
	void SetActive();
	inline const int GetWidth() const { return width; }
	inline const int GetHeight() const { return height; }

private:
	unsigned int textureID;
	int width;
	int height;
};