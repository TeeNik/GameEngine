#include "Graphics/Mesh.hpp"
#include "Graphics/Renderer.hpp"
#include "Graphics/Texture.hpp"
#include "Graphics/VertexArray.hpp"
#include <fstream>
#include <sstream>
#include "../../Plugins/rapidjson/document.h"
#include "Math/Math.h"

Mesh::Mesh() : vertexArray(nullptr), 
radius(0.0f), 
specPower(100.0f),
box(Vector3::Infinity, Vector3::NegInfinity)
{
}

Mesh::~Mesh()
{
}

bool Mesh::Load(const std::string& fileName, Renderer* renderer)
{
	std::ifstream file(fileName);
	if (!file.is_open())
	{
		printf("File not found: Mesh %s", fileName.c_str());
		return false;
	}

	std::stringstream fileStream;
	fileStream << file.rdbuf();
	std::string contents = fileStream.str();
	rapidjson::StringStream jsonStr(contents.c_str());
	rapidjson::Document doc;
	doc.ParseStream(jsonStr);

	if (!doc.IsObject())
	{
		printf("Mesh %s is not valid json", fileName.c_str());
		return false;
	}

	int ver = doc["version"].GetInt();

	if (ver != 1)
	{
		printf("Mesh %s not version 1", fileName.c_str());
		return false;
	}

	shaderName = doc["shader"].GetString();

	size_t vertSize = 8;

	const rapidjson::Value& textureJson = doc["textures"];
	if (!textureJson.IsArray() || textureJson.Size() < 1)
	{
		printf("Mesh %s has no textures, there should be at least one", fileName.c_str());
		return false;
	}

	specPower = static_cast<float>(doc["specularPower"].GetDouble());

	for (rapidjson::SizeType i = 0; i < textureJson.Size(); i++)
	{
		std::string texName = textureJson[i].GetString();
		Texture* t = renderer->GetTexture(texName);
		if (t == nullptr)
		{
			t = renderer->GetTexture("Assets/Default.png");
		}
		textures.emplace_back(t);
	}

	const rapidjson::Value& vertsJson = doc["vertices"];
	if (!vertsJson.IsArray() || vertsJson.Size() < 1)
	{
		printf("Mesh %s has no vertices", fileName.c_str());
		return false;
	}

	std::vector<float> vertices;
	vertices.reserve(vertsJson.Size() * vertSize);
	radius = 0.0f;
	for (rapidjson::SizeType i = 0; i < vertsJson.Size(); i++)
	{
		const rapidjson::Value& vert = vertsJson[i];
		if (!vert.IsArray() || vert.Size() != 8)
		{
			printf("Unexpected vertex format for %s", fileName.c_str());
			return false;
		}

		Vector3 pos(vert[0].GetDouble(), vert[1].GetDouble(), vert[2].GetDouble());
		radius = Math::Max(radius, pos.LengthSq());
		box.UpdateMinMax(pos);

		for (rapidjson::SizeType i = 0; i < vert.Size(); i++)
		{
			vertices.emplace_back(static_cast<float>(vert[i].GetDouble()));
		}
	}

	radius = Math::Sqrt(radius);

	const rapidjson::Value& indJson = doc["indices"];
	if (!indJson.IsArray() || indJson.Size() < 1)
	{
		printf("Mesh %s has no indices", fileName.c_str());
		return false;
	}

	std::vector<unsigned int> indices;
	indices.reserve(indJson.Size() * 3);
	for (rapidjson::SizeType i = 0; i < indJson.Size(); i++)
	{
		const rapidjson::Value& ind = indJson[i];
		if (!ind.IsArray() || ind.Size() != 3)
		{
			printf("Invalid indices for %s", fileName.c_str());
			return false;
		}

		indices.emplace_back(ind[0].GetUint());
		indices.emplace_back(ind[1].GetUint());
		indices.emplace_back(ind[2].GetUint());
	}

	vertexArray = new VertexArray(vertices.data(), static_cast<unsigned>(vertices.size()) / vertSize,
		indices.data(), static_cast<unsigned>(indices.size()));
	return true;
}

void Mesh::Unload()
{
	delete vertexArray;
	vertexArray = nullptr;
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