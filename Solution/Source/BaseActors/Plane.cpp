#pragma once
#include "BaseActors/Plane.hpp"
#include "Utils/Utils.hpp"
#include "ObjectSystem/MeshComponent.hpp"
#include "Engine/Engine.hpp"
#include "Graphics/Renderer.hpp"

Plane::Plane(Engine* e) : Actor(e)
{
	SetActorScale(InitialScale);
	mc = new MeshComponent(this);
	mc->SetMesh(GetEngine()->GetRenderer()->GetMesh("Assets/Plane.gpmesh"));
}