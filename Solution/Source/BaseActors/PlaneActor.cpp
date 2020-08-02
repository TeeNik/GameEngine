#include "BaseActors/PlaneActor.hpp"
#include "Utils/Utils.hpp"
#include "ObjectSystem/MeshComponent.hpp"
#include "Engine/Engine.hpp"
#include "Graphics/Renderer.hpp"
#include "ObjectSystem/Collision/BoxComponent.hpp"
#include "Graphics/Mesh.hpp"

PlaneActor::PlaneActor(Engine* e) : Actor(e)
{
	SetActorScale(InitialScale);
	mc = AddComponent<MeshComponent>();
	Mesh* mesh = GetEngine()->GetRenderer()->GetMesh("Assets/Plane.gpmesh");
	mc->SetMesh(mesh);

	box = AddComponent<BoxComponent>();
	box->SetObjectType(CollisionObjectType::Static);
	box->SetObjectBox(mesh->GetBox());
}