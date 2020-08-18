#include "Graphics/Lighting/PointLight.hpp"
#include "Graphics/Shader.hpp"
#include <string>

PointLight::PointLight(Engine* e) : Actor(e)
{
	AddComponent<PointLightComponent>();
}

void PointLight::AddLightToShader(Shader* shader, const int index)
{
	std::string str = "pointLights[" + index + std::string("]");
	shader->SetVectorUniform((str + ".position").c_str(), GetActorPosition());
	shader->SetVectorUniform((str + ".ambient").c_str(),light.ambient);
	shader->SetVectorUniform((str + ".diffuse").c_str(),light.diffuse);
	shader->SetVectorUniform((str + ".specular").c_str(), light.specular);
	shader->SetFloatUniform((str + ".constant").c_str(), constant);
	shader->SetFloatUniform((str + ".linear").c_str(), linear);
	shader->SetFloatUniform((str + ".quadratic").c_str(), quadratic);
}