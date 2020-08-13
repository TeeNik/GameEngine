#include "Graphics\Materials\LightMaterial.hpp"

void LightMaterial::Use(Shader * shader)
{
	Vector3 objColor(0.804f, 0.408, 0.537);
	shader->SetVectorUniform("uObjectColor", objColor);
	shader->SetVectorUniform("uLightColor", Vector3(1, 1, 1));
}
