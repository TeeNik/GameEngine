#pragma once
#include <string>
#include <vector>
#include "Physics/Collision.hpp"

class Renderer;
class VertexArray;
class Texture;
struct AABB;

class Mesh
{
public:
	Mesh();
	~Mesh();
	
	bool Load(const std::string& fileName, class Renderer* renderer);
	void Unload();
	
	VertexArray* GetVertexArray() { return vertexArray; }
	Texture* GetTexture(size_t index);
	
	inline const std::string& GetShaderName() const { return shaderName; }
	inline float GetRadius() const { return radius; }
	inline float GetSpecPower() const { return specPower; }
	inline const AABB& GetBox() { return box; }

private:
	AABB box;
	std::vector<Texture*> textures;
	class VertexArray* vertexArray;
	std::string shaderName;
	float radius;
	float specPower;
};