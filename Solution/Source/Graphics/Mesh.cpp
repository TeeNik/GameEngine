#include "Graphics/Mesh.hpp"
#include "Graphics/Renderer.hpp"
#include "Graphics/Texture.hpp"
#include "Graphics/VertexArray.hpp"
#include "Math/Math.h"
#include "Engine/Engine.hpp"
#include "Graphics/Shader.hpp"

#include "Utils/Utils.hpp"
#include "glew.h"
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <cassert>
#include <iostream>
#include <fstream>

Mesh::Mesh(const aiMesh* m, const aiScene* scene, Engine* e) :
	radius(0.0f),
	specPower(100.0f),
	box(Vector3::Infinity, Vector3::NegInfinity)
{
	engine = e;

	for (int i = 0; i < m->mNumVertices; ++i)
	{
		Vertex vertex;

		auto pos = m->mVertices[i];
		vertex.position.x = pos.x;
		vertex.position.y = pos.y;
		vertex.position.z = pos.z;

		if (m->HasNormals())
		{
			auto normal = m->mNormals[i];
			vertex.normal.x = normal.x;
			vertex.normal.y = normal.y;
			vertex.normal.z = normal.z;
		}

		if (m->mTextureCoords[0])
		{
			auto tex = m->mTextureCoords[0][i];
			vertex.texCoords.x = tex.x;
			vertex.texCoords.y = tex.y;
		}
		else {
			vertex.texCoords = Vector2::Zero;
		}

		vertices.push_back(vertex);
	}

	for (int i = 0; i < m->mNumFaces; ++i)
	{
		auto face = m->mFaces[i];
		for (int j = 0; j < face.mNumIndices; ++j)
		{
			indices.emplace_back(face.mIndices[j]);
		}
	}

	if (scene->mTextures > 0) {
		SetTexture(engine->GetRenderer()->GetTexture(scene, m));
	}

	printf("Mesh complete");
}

Mesh::~Mesh()
{
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO);
}

void Mesh::SetupMesh()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

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

	CalculateBox(vertices);
}

/*
void Mesh::SetTexture(Renderer* renderer, const std::string& path)
{
	textures.emplace_back(renderer->GetTexture(path));
}
*/

void Mesh::SetTexture(Texture* t)
{
	textures.emplace_back(t);
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
