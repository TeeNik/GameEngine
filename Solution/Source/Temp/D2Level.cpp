#include "Temp/D2Level.hpp"
#include "Engine/Engine.hpp"
#include "ObjectSystem/ObjectManager.hpp"
#include "ObjectSystem/MeshComponent.hpp"
#include "Temp/Player2D.hpp"
#include "Temp/Player.hpp"
#include "Graphics/Renderer.hpp"
#include "Graphics/Mesh.hpp"
#include "Temp/RotateAroundComponent.hpp"

#include "Graphics/Light/PointLight.hpp"
#include "Graphics/Light/LightingSystem.hpp"
#include "Graphics/Light/Material.hpp"

#include "Utils/Utils.hpp"
#include "Graphics/MeshExporter.hpp"

D2Level::D2Level(Engine * e) : Level(e)
{
}

void D2Level::Load()
{
	auto ECS = engine->GetObjectManager();
	auto renderer = engine->GetRenderer();

	Player* player = ECS->SpawnActor<Player>();

	PointLight* light = ECS->SpawnActor<PointLight>();

	auto cube = ECS->SpawnActor<Actor>();
	cube->SetActorScale(Vector3(10, 10, 10));
	cube->SetActorPosition(Vector3(-20, -20, 0));
	auto mc = cube->AddComponent<MeshComponent>();
	auto mesh = renderer->GetMesh(Utils::ContructPath("models/transp/transp.obj"));
	mc->SetMesh(mesh);
	mc->SetShaderName("Phong|Blending");
	auto texture = renderer->GetTexture(Utils::ContructPath("window.png"));
	auto mat = new Material();
	mat->diffuse = texture;
	mat->shininess = 32;
	mc->SetMaterial(mat);
	//auto rc = cube->AddComponent<RotateAroundComponent>();
	//rc->SetRotation(Vector3::Zero, 2);


}

void D2Level::Unload()
{
}
