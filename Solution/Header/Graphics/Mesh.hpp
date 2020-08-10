#pragma once
#include <string>
#include <vector>
#include "Physics/Collision.hpp"

class Renderer;
class VertexArray;
class Texture;
struct AABB;
class Shader;

struct Vertex
{
	Vector3 position;
	Vector3 normal;
	Vector2 texCoords;
};

class Mesh
{
public:
	Mesh();
	~Mesh();
	
	bool Load(const std::string& fileName, class Renderer* renderer);
	void Unload();

	void SetData(Renderer* renderer);
	
	Texture* GetTexture(size_t index);
	
	inline const std::string& GetShaderName() const { return shaderName; }
	inline float GetRadius() const { return radius; }
	inline float GetSpecPower() const { return specPower; }
	inline const AABB& GetBox() { return box; }

	void Draw(Shader* shader);
	void SetupMesh(const std::vector<Vertex>& v, const std::vector<unsigned int>& ind);

private:
	void CalculateBox(const std::vector<Vertex>& v);

	AABB box;

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	unsigned int VAO, VBO, EBO;

	std::vector<Texture*> textures;
	std::string shaderName;
	float radius;
	float specPower;
};