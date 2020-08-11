#include "Temp/D2Level.hpp"
#include "Engine/Engine.hpp"
#include "ObjectSystem/ObjectManager.hpp"
#include "ObjectSystem/MeshComponent.hpp"
#include "Temp/Player2D.hpp"
#include "Temp/Player.hpp"
#include "Graphics/Renderer.hpp"
#include "Graphics/Mesh.hpp"

#include "Utils/Utils.hpp"
#include "Graphics/MeshExporter.hpp"

D2Level::D2Level(Engine * e) : Level(e)
{
}

void D2Level::Load()
{
	auto ECS = engine->GetObjectManager();
	auto renderer = engine->GetRenderer();
	//Player2D* player = ECS->SpawnActor<Player2D>();

	Player* player = ECS->SpawnActor<Player>();
	auto path = Utils::ContructPath("models/lighthouse/lighthouse.obj");

	Actor* actor = ECS->SpawnActor<Actor>();
	actor->SetActorRotation(Quaternion(Vector3::UnitX, Math::PiOver2));
	auto mc = actor->AddComponent<MeshComponent>();
	auto mesh = engine->GetRenderer()->GetMesh(path);
	mesh->SetTexture(renderer, Utils::ContructPath("models/lighthouse/Lighthouse.png"));
	auto box = mesh->GetBox();
	mc->SetMesh(mesh);

	return;

	actor = ECS->SpawnActor<Actor>();
	path = Utils::ContructPath("models/cube/cube.obj");
	mc = actor->AddComponent<MeshComponent>();
	mesh = engine->GetRenderer()->GetMesh(path);
	mesh->SetTexture(renderer, Utils::ContructPath("models/cube/cube_border.png"));
	mc->SetMesh(mesh);
	
	Vector3 scale;
	scale.x = Math::Abs(box.max.x - box.min.x);
	scale.y = Math::Abs(box.max.y - box.min.y);
	scale.z = Math::Abs(box.max.z - box.min.z);
	actor->SetActorScale(scale * 0.5f);
}

void D2Level::Unload()
{
}
