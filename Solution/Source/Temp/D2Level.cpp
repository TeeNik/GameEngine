#include "Temp/D2Level.hpp"
#include "Engine/Engine.hpp"
#include "ObjectSystem/ObjectManager.hpp"
#include "ObjectSystem/MeshComponent.hpp"
#include "Temp/Player2D.hpp"
#include "Temp/Player.hpp"
#include "Graphics/Renderer.hpp"

#include "Utils/Utils.hpp"
#include "Graphics/Model.hpp"


D2Level::D2Level(Engine * e) : Level(e)
{
}

void D2Level::Load()
{
	auto ECS = engine->GetObjectManager();
	//Player2D* player = ECS->SpawnActor<Player2D>();

	Player* player = ECS->SpawnActor<Player>();
	auto path = Utils::ContructPath("models/lighthouse/lighthouse.obj");

	Actor* actor = ECS->SpawnActor<Actor>();
	actor->SetActorRotation(Quaternion(Vector3::UnitX, Math::PiOver2));
	auto mc = actor->AddComponent<MeshComponent>();
	mc->SetMesh(engine->GetRenderer()->GetMesh(path));
}

void D2Level::Unload()
{
}
