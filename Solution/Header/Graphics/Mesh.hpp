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
	Mesh(const std::vector<Vertex>& v, const std::vector<unsigned int>& ind);
	~Mesh();
	
	void SetTexture(Renderer* renderer, const std::string& path);
	
	Texture* GetTexture(size_t index);

	inline float GetRadius() const { return radius; }
	inline float GetSpecPower() const { return specPower; }
	inline const AABB& GetBox() { return box; }

	void Draw(Shader* shader);

private:
	void CalculateBox(const std::vector<Vertex>& v);

	AABB box;

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	unsigned int VAO, VBO, EBO;

	std::vector<Texture*> textures;
	float radius;
	float specPower;
};