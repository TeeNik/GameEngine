#pragma once
#include "ObjectSystem/Component.hpp"
#include <cstddef>

class Actor;
class Mesh;
class Shader;

class MeshComponent : public Component
{
public:
	MeshComponent(Actor* owner);
	~MeshComponent();
	
	virtual void Draw(Shader* shader);
	
	virtual void SetMesh(Mesh* mesh) { mesh = mesh; }
	void SetTextureIndex(size_t index) { textureIndex = index; }
protected:
	Mesh* mesh;
	size_t textureIndex;
};