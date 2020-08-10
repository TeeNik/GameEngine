#include "ObjectSystem/MeshComponent.hpp"
#include "Graphics/Shader.hpp"
#include "Graphics/Mesh.hpp"
#include "ObjectSystem/Actor.hpp"
#include "Engine/Engine.hpp"
#include "Graphics/Renderer.hpp"
#include "Graphics/Texture.hpp"
#include "Graphics/VertexArray.hpp"

MeshComponent::MeshComponent(Actor* owner)
	: Component(owner),
	mesh(nullptr),
	textureIndex(0)
{
	updateOrder = 0;
	owner->GetEngine()->GetRenderer()->AddMeshComp(this);
}

MeshComponent::~MeshComponent()
{
	owner->GetEngine()->GetRenderer()->RemoveMeshComp(this);
}

void MeshComponent::Draw(Shader* shader)
{
	if (mesh)
	{
		shader->SetMatrixUniform("uWorldTransform", owner->GetWorldTransform());
		
		shader->SetFloatUniform("uSpecPower", mesh->GetSpecPower());
		
		Texture* t = mesh->GetTexture(textureIndex);
		if (t)
		{
			t->SetActive();
		}
		
		//VertexArray* va = mesh->GetVertexArray();
		//va->SetActive();
		//
		//glDrawElements(GL_TRIANGLES, va->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
	
		mesh->Draw(shader);
	}
}