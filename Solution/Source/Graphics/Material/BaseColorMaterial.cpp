#include "Graphics/Materials/BaseColorMaterial.hpp"

void BaseColorMaterial::Use(Shader * shader)
{
	shader->SetVectorUniform("color", color);
}
