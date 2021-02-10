#pragma once
#include <vector>
#include "Physics/Collision.hpp"
#include <map>
#include <string>
#include <assimp/matrix4x4.h>
#include <assimp/Importer.hpp>
#include "Math/Math.h"
#include <assimp/anim.h>
#include <glew.h>

class Engine;
struct aiAnimation;
struct aiMesh;
struct aiNode;
class Renderer;
class VertexArray;
class Texture;
struct AABB;
class Shader;

class aiScene;

struct Vertex
{
	Vector3 position;
	Vector3 normal;
	Vector2 texCoords;
};

class Mesh
{
public:
	Mesh(const aiMesh* m, const aiScene* scene, Engine* e);
	virtual ~Mesh();
	
	//void SetTexture(Renderer* renderer, const std::string& path);
	
	void SetTexture(Texture* t);
	Texture* GetTexture(size_t index);

	inline float GetRadius() const { return radius; }
	inline float GetSpecPower() const { return specPower; }
	inline const AABB& GetBox() { return box; }

	virtual void Draw(Shader* shader);

	virtual void SetupMesh();
	class Engine* engine;

protected:
	void CalculateBox(const std::vector<Vertex>& v);

	AABB box;
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	unsigned int VAO, VBO, EBO, VBO_bones;

	std::vector<Texture*> textures;
	float radius;
	float specPower;
};