#include "Graphics/Light/PointLight.hpp"
#include "Graphics/Shader.hpp"
#include <string>
#include "Engine/Engine.hpp"
#include "Graphics/Renderer.hpp"
#include "Graphics/Light/LightingSystem.hpp"
#include "Utils/Utils.hpp"
#include "ObjectSystem/MeshComponent.hpp"
#include "Graphics/Light/Material.hpp"

PointLight::PointLight(Engine* e) : Actor(e)
{
	auto renderer = e->GetRenderer();
	renderer->GetLighting()->RegisterLight(this);

	auto mesh = renderer->GetMesh(Utils::ContructPath("models/cube/cube.obj"));
	auto mc = AddComponent<MeshComponent>();
	mc->SetShaderName("Phong|BasicMesh");
	mc->SetMesh(mesh);

	auto material = new Material();
	material->baseColor = Vector3(.5f, .5f, 0);
	mc->SetMaterial(material);
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