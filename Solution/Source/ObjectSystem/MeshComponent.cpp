#include "ObjectSystem/MeshComponent.hpp"
#include "Graphics/Shader.hpp"
#include "Graphics/Mesh.hpp"
#include "ObjectSystem/Actor.hpp"
#include "Engine/Engine.hpp"
#include "Graphics/Renderer.hpp"
#include "Graphics/Texture.hpp"
#include "Graphics/VertexArray.hpp"
#include "Graphics/Materials/Material.hpp"

MeshComponent::MeshComponent(Actor* owner)
	: Component(owner),
	mesh(nullptr),
	textureIndex(0),
	shaderName("BasicMesh|BasicMesh")
{
	updateOrder = 0;
	owner->GetEngine()->GetRenderer()->AddMeshComp(this);
}

MeshComponent::~MeshComponent()
{
	delete material;

	owner->GetEngine()->GetRenderer()->RemoveMeshComp(this);
}

void MeshComponent::Draw(Shader* shader)
{
	if (mesh)
	{
		shader->SetMatrixUniform("uWorldTransform", owner->GetWorldTransform());
		shader->SetFloatUniform("uSpecPower", mesh->GetSpecPower());
		
		if (material != nullptr)
		{
			material->Use(shader);
		}

		Texture* t = mesh->GetTexture(textureIndex);
		if (t)
		{
			t->SetActive();
		}
		mesh->Draw(shader);
	}
}