#include "Graphics\Texture.hpp"
#include "SOIL.h"
#include "glew.h"
#include "SDL.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

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
	return CreateFromImage(image, channels, fileName);
}

bool Texture::Load(const aiScene* scene, std::string& textureName)
{
	aiTexture* aiTex = nullptr;
	for (int i = 0; i < scene->mNumTextures; ++i)
	{
		aiTexture* t = scene->mTextures[i];
		if (t->mFilename.C_Str() == textureName)
		{
			aiTex = scene->mTextures[i];
			break;
		}
	}

	if (aiTex == nullptr)
	{
		printf("aiTexure is not found in %s", textureName.c_str());
		return false;
	}

	int channels = 0;
	unsigned char* image = SOIL_load_image_from_memory(reinterpret_cast<unsigned char*>(aiTex->pcData), aiTex->mWidth, &width, &height, &channels, SOIL_LOAD_AUTO);
	return CreateFromImage(image, channels, textureName);
}

bool Texture::CreateFromImage(unsigned char* image, int channels, const std::string& filename)
{
	size.x = width;
	size.y = height;

	if (image == nullptr) {
		printf("SOIL failed to load image %s: %s", filename.c_str(), SOIL_last_result());
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

void Texture::SetActive(int bindIndex)
{
	glActiveTexture(bindIndex);
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::CreateFromSurface(SDL_Surface* surface)
{
	width = surface->w;
	height = surface->h;

	size.x = width;
	size.y = height;

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, surface->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}