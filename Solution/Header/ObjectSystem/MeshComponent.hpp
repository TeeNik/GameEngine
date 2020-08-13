#pragma once
#include "ObjectSystem/Component.hpp"
#include <cstddef>
#include <string>
#include "Graphics/Mesh.hpp"

class Actor;
class Shader;
class Model;
class Material;

class MeshComponent : public Component
{
public:
	MeshComponent(Actor* owner);
	~MeshComponent();
	
	virtual void Draw(Shader* shader);
	
	inline void SetShaderName(const std::string shader) { shaderName = shader; }
	inline void SetMaterial(Material* m) { material = m; }
	inline void SetMesh(Mesh* m) { mesh = m; }
	inline const std::string& GetShaderName() { return shaderName; }

	void SetTextureIndex(size_t index) { textureIndex = index; }
protected:
	//TODO move material owning to Renderer
	Material* material = nullptr;
	std::string shaderName;

	Mesh* mesh;
	size_t textureIndex;
};