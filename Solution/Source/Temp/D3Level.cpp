#include "Temp/D3Level.hpp"
#include "BaseActors/PlaneActor.hpp"
#include "BaseActors/Camera.hpp"
#include "Temp/Player.hpp"
#include "ObjectSystem/MeshComponent.hpp"
#include "Graphics/Renderer.hpp"
#include "ObjectSystem/ObjectManager.hpp"
#include "ObjectSystem/Actor.hpp"
#include "Utils/Utils.hpp"
#include "Engine/Engine.hpp"
#include "ObjectSystem/SpriteRendererComponent.hpp"

D3Level::D3Level(Engine * e) : Level(e)
{
}

void D3Level::Load()
{
	auto ECS = engine->GetObjectManager();
	auto renderer = engine->GetRenderer();
	Actor* a = ECS->SpawnActor<Actor>();
	a->SetActorPosition(Vector3(200.0f, 75.0f, 0.0f));
	a->SetActorScale(Vector3(100, 100, 100));
	Quaternion q(Vector3::UnitY, -Math::PiOver2);
	q = Quaternion::Concatenate(q, Quaternion(Vector3::UnitZ, Math::Pi + Math::Pi / 4.0f));
	a->SetActorRotation(q);
	MeshComponent* mc = a->AddComponent<MeshComponent>();
	mc->SetMesh(renderer->GetMesh(Utils::ContructPath("Cube.gpmesh")));

	a = ECS->SpawnActor<Actor>();
	a->SetActorPosition(Vector3(200.0f, -75.0f, 0.0f));
	a->SetActorScale(Vector3(3, 3, 3));
	mc = a->AddComponent<MeshComponent>();
	mc->SetMesh(renderer->GetMesh(Utils::ContructPath("Sphere.gpmesh")));

	// Setup floor
	const float start = -1250.0f;
	const float size = 250.0f;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			a = ECS->SpawnActor<PlaneActor>();
			a->SetActorPosition(Vector3(start + i * size, start + j * size, -100.0f));
		}
	}

	// Left/right walls
	q = Quaternion(Vector3::UnitX, Math::PiOver2);
	for (int i = 0; i < 10; i++)
	{
		a = ECS->SpawnActor<PlaneActor>();
		a->SetActorPosition(Vector3(start + i * size, start - size, 0.0f));
		a->SetActorRotation(q);

		a = ECS->SpawnActor<PlaneActor>();
		a->SetActorPosition(Vector3(start + i * size, -start + size, 0.0f));
		a->SetActorRotation(q);
	}

	q = Quaternion::Concatenate(q, Quaternion(Vector3::UnitZ, Math::PiOver2));
	// Forward/back walls
	for (int i = 0; i < 10; i++)
	{
		a = ECS->SpawnActor<PlaneActor>();
		a->SetActorPosition(Vector3(start - size, start + i * size, 0.0f));
		a->SetActorRotation(q);

		a = ECS->SpawnActor<PlaneActor>();
		a->SetActorPosition(Vector3(-start + size, start + i * size, 0.0f));
		a->SetActorRotation(q);
	}

	// Setup lights
	renderer->SetAmbientLight(Vector3(0.2f, 0.2f, 0.2f));
	DirectionalLight& dir = renderer->GetDirectionalLight();
	dir.direction = Vector3(0.0f, -0.707f, -0.707f);
	dir.diffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	dir.specColor = Vector3(0.8f, 0.8f, 0.8f);

	// Camera actor
	Player* playerCamera = ECS->SpawnActor<Player>();

	// UI elements
	a = ECS->SpawnActor<Actor>();
	a->SetActorPosition(Vector3(-350.0f, -350.0f, 0.0f));
	SpriteRendererComponent* sc = a->AddComponent<SpriteRendererComponent>();
	sc->SetTexture("../Solution/Assets/HealthBar.png");

	a = ECS->SpawnActor<Actor>();
	a->SetActorPosition(Vector3(375.0f, -275.0f, 0.0f));
	a->SetActorScale(Vector3(0.75f, 0.75f, 0.75f));
	sc = a->AddComponent<SpriteRendererComponent>();
	sc->SetTexture("../Solution/Assets/Radar.png");
}

void D3Level::Unload()
{
}
