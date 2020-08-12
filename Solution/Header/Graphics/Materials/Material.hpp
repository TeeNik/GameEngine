#pragma once
#include <string>
#include "Graphics/Shader.hpp"

class Material
{
public:
	virtual void Use(Shader* shader);

	const std::string name;

};