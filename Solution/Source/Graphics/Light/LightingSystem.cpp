#include "Graphics/Lighting/LightingSystem.hpp"
#include "ObjectSystem/LightComponent.hpp"
#include "Graphics/Lighting/PointLight.hpp"
#include "Graphics/Shader.hpp"

void LightingSystem::Update(Shader* shader)
{
	ProcessPointLights(shader);
}

void LightingSystem::RegisterLight(PointLight* light)
{
}

void LightingSystem::ProcessPointLights(Shader* shader)
{
	shader->SetIntUniform("numOfPointLights", pointLights.size());

	for (int i = 0; i < pointLights.size(); ++i)
	{
		pointLights[i].AddLightToShader(shader, i);
	}
}
