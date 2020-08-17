#include "ObjectSystem/LightComponent.hpp"
#include "ObjectSystem/Actor.hpp"
#include "Graphics/Lighting/LightingSystem.hpp"
#include "Graphics/Renderer.hpp"
#include "Engine/Engine.hpp"

LightComponent::LightComponent(Actor* o) : Component(o)
{
	o->GetEngine()->GetRenderer()->GetLighting()->RegisterLight(this);
}
