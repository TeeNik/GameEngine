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

#include "ObjectSystem/SpriteRendererComponent.hpp"
#include "ObjectSystem/Collision/BoxComponent.hpp"

D2Level::D2Level(Engine * e) : Level(e)
{
}

void D2Level::Load()
{
	auto ECS = engine->GetObjectManager();
	auto renderer = engine->GetRenderer();

	//Player2D* player = ECS->SpawnActor<Player2D>();
	//
	//auto obstacle = ECS->SpawnActor<Actor>();
	//obstacle->SetActorPosition(Vector3(0, 150, 0));
	//auto sc = obstacle->AddComponent<SpriteRendererComponent>();
	//sc->SetTexture(Utils::ContructPath("border.png"));
	//sc->SetSize(Vector2(100, 100));
	//auto halfSize = Vector3(sc->GetSize().x, sc->GetSize().y, 0) * .5;
	//AABB aabb(halfSize * -1, halfSize);
	//auto box = obstacle->AddComponent<BoxComponent>();
	//box->SetObjectBox(aabb);
	//box->SetObjectType(CollisionObjectType::Static);
	//box->NextPos = obstacle->GetActorPosition();
	//
	//return;

	Player* player = ECS->SpawnActor<Player>();
	auto character = ECS->SpawnActor<Actor>();
	auto mc = character->AddComponent<MeshComponent>();
	auto mesh = renderer->GetMesh(Utils::ContructPath("models/char/Walking.fbx"));
	character->SetActorScale(Vector3(.5f, .5f, .5f));
	character->SetActorRotation(Quaternion(Vector3::UnitX, Math::PiOver2));
	mc->SetMesh(mesh);
	mc->SetShaderName("AnimatedModel|BasicMesh");
	//auto mat = new Material();
	//mat->diffuse = renderer->GetTexture(mesh->GetSceneData(), mesh->GetMeshData());
	//mc->SetMaterial(mat);

	//PointLight* light = ECS->SpawnActor<PointLight>();
}

void D2Level::Unload()
{
}
