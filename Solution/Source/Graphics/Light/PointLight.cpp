#include "Graphics\Light\PointLight.hpp"
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
	SetActorScale(Vector3::One * 4);

	auto renderer = e->GetRenderer();
	renderer->GetLighting()->RegisterLight(this);

	auto mesh = renderer->GetMesh(Utils::ContructPath("models/cube/cube.obj"));
	auto mc = AddComponent<MeshComponent>();
	mc->SetShaderName("Phong|BasicMesh");
	mc->SetMesh(mesh);

	auto material = new Material();
	material->baseColor = Vector3(1, 1, 1);
	mc->SetMaterial(material);

	light.ambient = Vector3(.2, .2, .2);
	light.diffuse = Vector3(.5, .5, .5);
	light.specular = Vector3(1, 1, 1);

	linear = 0.027f;
	quadratic = .0028f;

	renderer->GetLighting()->RegisterLight(this);
}

void PointLight::AddLightToShader(Shader* shader, const int index)
{
	std::string str = "pointLights[" + std::to_string(index) + std::string("]");
	shader->SetVectorUniform((str + ".position").c_str(), GetActorPosition());
	shader->SetVectorUniform((str + ".ambient").c_str(), light.ambient);
	shader->SetVectorUniform((str + ".diffuse").c_str(), light.diffuse);
	shader->SetVectorUniform((str + ".specular").c_str(), light.specular);
	shader->SetFloatUniform((str + ".constant").c_str(), constant);
	shader->SetFloatUniform((str + ".linear").c_str(), linear);
	shader->SetFloatUniform((str + ".quadratic").c_str(), quadratic);
}
