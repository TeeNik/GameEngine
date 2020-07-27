#include "ObjectSystem/Camera/CameraComponent.hpp"
#include "ObjectSystem/Actor.hpp"
#include "Engine/Engine.hpp"
#include "Graphics/Renderer.hpp"

CameraComponent::CameraComponent(Actor* o) : Component(o)
{

}

void CameraComponent::SetViewMatrix(const Matrix4& view)
{
	owner->GetEngine()->GetRenderer()->SetViewMatrix(view);
}
