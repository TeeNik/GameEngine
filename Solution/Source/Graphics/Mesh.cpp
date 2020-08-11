#include "Graphics/Mesh.hpp"
#include "Graphics/Renderer.hpp"
#include "Graphics/Texture.hpp"
#include "Graphics/VertexArray.hpp"
#include <fstream>
#include <sstream>
#include "../../Plugins/rapidjson/document.h"
#include "Math/Math.h"
#include "Engine/Engine.hpp"
#include "Graphics/Shader.hpp"

#include "Utils/Utils.hpp"
#include "glew.h"

Mesh::Mesh(const std::vector<Vertex>& v, const std::vector<unsigned int>& ind) :
	radius(0.0f), 
	specPower(100.0f),
	shaderName("BasicMesh"),
	box(Vector3::Infinity, Vector3::NegInfinity)
{
	vertices = v;
	indices = ind;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
		&indices[0], GL_STATIC_DRAW);

	// vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	// vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));

	glBindVertexArray(0);

	CalculateBox(v);
}

Mesh::~Mesh()
{
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO);
}

void Mesh::SetTexture(Renderer* renderer, const std::string& path)
{
	textures.emplace_back(renderer->GetTexture(path));
}

Texture* Mesh::GetTexture(size_t index)
{
	if (index < textures.size())
	{
		return textures[index];
	}
	else
	{
		return nullptr;
	}
}

void Mesh::Draw(Shader * shader)
{
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);
}

void Mesh::CalculateBox(const std::vector<Vertex>& vertices)
{
	for (auto& v : vertices)
	{
		radius = Math::Max(radius, v.position.LengthSq());
		box.UpdateMinMax(v.position);
	}
	radius = Math::Sqrt(radius);
}