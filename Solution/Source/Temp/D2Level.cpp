#include "Temp/D2Level.hpp"
#include "Engine/Engine.hpp"
#include "ObjectSystem/ObjectManager.hpp"
#include "ObjectSystem/MeshComponent.hpp"
#include "Temp/Player2D.hpp"
#include "Temp/Player.hpp"
#include "Graphics/Renderer.hpp"
#include "Graphics/Mesh.hpp"

#include "Graphics/Materials/LightMaterial.hpp"
#include "Graphics/Materials/BaseColorMaterial.hpp"

#include "Utils/Utils.hpp"
#include "Graphics/MeshExporter.hpp"

D2Level::D2Level(Engine * e) : Level(e)
{
}

void D2Level::Load()
{
	auto ECS = engine->GetObjectManager();
	auto renderer = engine->GetRenderer();

	auto light = ECS->SpawnActor<Actor>();
	auto mesh = renderer->GetMesh(Utils::ContructPath("models/cube/cube.obj"));
	auto baseColor = new BaseColorMaterial();
	baseColor->SetColor(Vector3(0, 1, 1));
	auto mc = light->AddComponent<MeshComponent>();
	mc->SetShaderName("BasicMesh|SolidColor");
	mc->SetMesh(mesh);
	mc->SetMaterial(baseColor);
	light->SetActorScale(Vector3(10, 10, 10));

	auto cube = ECS->SpawnActor<Actor>();
	cube->SetActorScale(Vector3(4, 4, 4));
	cube->SetActorPosition(Vector3(-20, -20, 0));
	mc = cube->AddComponent<MeshComponent>();
	mc->SetMesh(mesh);
	mc->SetShaderName("BasicMesh|Light");
	mc->SetMaterial(new LightMaterial());

	Player* player = ECS->SpawnActor<Player>();
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
