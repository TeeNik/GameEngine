#pragma once
#include <string>
#include "Graphics/Shader.hpp"

class Material
{
public:
	Vector3 baseColor;
	Vector3 ambient;
	Vector3 diffuse;
	Vector3 specular;
	float shininess;


	virtual void Use(Shader* shader);
};