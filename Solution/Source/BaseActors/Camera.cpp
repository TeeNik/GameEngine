#include "BaseActors/Camera.hpp"
#include "Engine/Engine.hpp"
#include "Graphics/Renderer.hpp"

Camera::Camera(Engine* e) : Actor(e)
{
}

void Camera::Update(float deltaTime)
{
	Actor::Update(deltaTime);

	Vector3 cameraPos = GetActorLocation();
	Vector3 target = cameraPos + GetForward() * 100.0f;
	Vector3 up = Vector3::UnitZ;

	Matrix4 view = Matrix4::CreateLookAt(cameraPos, target, up);
	GetEngine()->GetRenderer()->SetViewMatrix(view);
}
