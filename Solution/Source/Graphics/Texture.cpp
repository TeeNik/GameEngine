#include "Graphics\Texture.hpp"
#include "SOIL.h"
#include "glew.h"
#include "SDL.h"

Texture::Texture() : textureID(0), width(0), height(0)
{
}

Texture::~Texture()
{
}

bool Texture::Load(const std::string& fileName)
{
	int channels = 0;
	unsigned char* image = SOIL_load_image(fileName.c_str(), &width, &height, &channels, SOIL_LOAD_AUTO);

	if (image == nullptr) {
		printf("SOIL failed to load image %s: %s", fileName.c_str(), SOIL_last_result());
		return false;
	}

	int format = channels == 4 ? GL_RGBA : GL_RGB;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	return true;
}

void Texture::Unload()
{
	glDeleteTextures(1, &textureID);
}

void Texture::SetActive()
{
	glBindTexture(GL_TEXTURE_2D, textureID);
}
