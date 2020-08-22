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
	auto mesh = renderer->GetMesh(Utils::ContructPath("models/cube/cube.obj"));
	mc->SetMesh(mesh);
	mc->SetShaderName("Phong|Light");
	auto mat = new Material();
	mat->baseColor = Vector3(1, 1, 0);
	mat->shininess = 32;
	mc->SetMaterial(mat);
	//auto rc = cube->AddComponent<RotateAroundComponent>();
	//rc->SetRotation(Vector3::Zero, 2);

	//Player2D* player = ECS->SpawnActor<Player2D>();

	/*
	auto path = Utils::ContructPath("models/lighthouse/lighthouse.obj");

	Actor* actor = ECS->SpawnActor<Actor>();
	actor->SetActorRotation(Quaternion(Vector3::UnitX, Math::PiOver2));
	auto mc = actor->AddComponent<MeshComponent>();
	auto mesh = engine->GetRenderer()->GetMesh(path);
	mesh->SetTexture(renderer, Utils::ContructPath("models/lighthouse/Lighthouse.png"));
	auto box = mesh->GetBox();
	mc->SetMesh(mesh);

	actor = ECS->SpawnActor<Actor>();
	actor->SetActorRotation(Quaternion(Vector3::UnitX, Math::PiOver2));
	path = Utils::ContructPath("models/cube/cube.obj");
	mc = actor->AddComponent<MeshComponent>();
	mesh = engine->GetRenderer()->GetMesh(path);
	mesh->SetTexture(renderer, Utils::ContructPath("models/cube/cube_border.png"));
	mc->SetMesh(mesh);
	
	Vector3 scale;
	scale.x = Math::Abs(box.max.x - box.min.x);
	scale.y = Math::Abs(box.max.y - box.min.y);
	scale.z = Math::Abs(box.max.z - box.min.z);
	actor->SetActorScale(scale);
	*/
	
}

void D2Level::Unload()
{
}
