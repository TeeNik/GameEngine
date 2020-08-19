#pragma once
#include <string>
#include "Graphics/Shader.hpp"
#include "Graphics/Texture.hpp"

class Material
{
public:
	Vector3 baseColor;
	Texture* diffuse;
	Texture* specular;
	float shininess;
	int hasDiffuse;
	int hasSpecular;

	virtual void Use(Shader* shader);
};