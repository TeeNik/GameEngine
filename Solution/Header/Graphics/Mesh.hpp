#pragma once
#include <string>
#include <vector>

class Renderer;
class VertexArray;
class Texture;

class Mesh {
public:
	Mesh();
	~Mesh();

	bool Load(const std::string& fileName, Renderer* renderer);
	void Unload();
	inline VertexArray* GetVertexArray() { return vertexArray; }
	Texture* GetTextureArray(size_t index);

private:
	std::vector<Texture*> textures;
	VertexArray* vertexArray;
	std::string shaderName;
	float radius;
	float specularPower;
};