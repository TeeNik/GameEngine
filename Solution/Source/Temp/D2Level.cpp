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

	Player2D* player = ECS->SpawnActor<Player2D>();

	auto obstacle = ECS->SpawnActor<Actor>();
	obstacle->SetActorPosition(Vector3(0, 150, 0));
	auto sc = obstacle->AddComponent<SpriteRendererComponent>();
	sc->SetTexture(Utils::ContructPath("border.png"));
	sc->SetSize(Vector2(100, 100));
	auto halfSize = Vector3(sc->GetSize().x, sc->GetSize().y, 0) * .5;
	AABB aabb(halfSize * -1, halfSize);
	auto box = obstacle->AddComponent<BoxComponent>();
	box->SetObjectBox(aabb);
	box->SetObjectType(CollisionObjectType::Static);
	box->NextPos = obstacle->GetActorPosition();

	return;
	//Player* player1 = ECS->SpawnActor<Player>();

	//PointLight* light = ECS->SpawnActor<PointLight>();
	
	//auto cube = ECS->SpawnActor<Actor>();
	//cube->SetActorScale(Vector3(10, 10, 10));
	//cube->SetActorPosition(Vector3(-20, -20, 0));
	//auto mc = cube->AddComponent<MeshComponent>();
	//auto mesh = renderer->GetMesh(Utils::ContructPath("models/cube/cube.obj"));
	//mc->SetMesh(mesh);
	//mc->SetShaderName("Phong|Blending");
	//auto mat = new Material();
	//mat->baseColor = Vector3(1, 1, 0);
	//mat->shininess = 32;
	//mc->SetMaterial(mat);
	//
	//auto a = ECS->SpawnActor<Actor>();
	//a->SetActorPosition(Vector3(-350.0f, -350.0f, 0.0f));
	//SpriteRendererComponent* sc = a->AddComponent<SpriteRendererComponent>();
	//sc->SetTexture("../Solution/Assets/HealthBar.png");
	//
	//auto cube = ECS->SpawnActor<Actor>();
	//cube->SetActorScale(Vector3(10, 10, 10));
	//cube->SetActorPosition(Vector3(-20, -20, 0));
	//auto mc = cube->AddComponent<MeshComponent>();
	//auto mesh = renderer->GetMesh(Utils::ContructPath("models/transp/transp.obj"));
	//mc->SetMesh(mesh);
	//mc->SetShaderName("Phong|Blending");
	//auto texture = renderer->GetTexture(Utils::ContructPath("window.png"));
	//auto mat = new Material();
	//mat->diffuse = texture;
	//mat->shininess = 32;
	//mc->SetMaterial(mat);
	//auto rc = cube->AddComponent<RotateAroundComponent>();
	//rc->SetRotation(Vector3::Zero, 2);


}

void D2Level::Unload()
{
}
