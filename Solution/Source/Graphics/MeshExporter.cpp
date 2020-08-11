#include "Graphics/MeshExporter.hpp"
#include "Graphics/Mesh.hpp"
#include "Graphics/VertexArray.hpp"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "Engine/Engine.hpp"

MeshExporter::MeshExporter(Engine* e)
{
	engine = e;
}

std::vector<Mesh*>& MeshExporter::LoadMeshes(const std::string& path)
{
	meshes.clear();
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		printf("ERROR::ASSIMP %s\n", importer.GetErrorString());
	}
	else {
		ProcessNode(scene->mRootNode, scene);
	}
	return meshes;
}

Mesh * MeshExporter::LoadMesh(const std::string & path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		printf("ERROR::ASSIMP %s\n", importer.GetErrorString());
		return nullptr;
	}
	if (scene->mNumMeshes > 1)
	{
		printf("ERROR NumMeshes > 1");
		return nullptr;
	}

	return ProcessMesh(scene->mMeshes[0], scene);
}

void MeshExporter::ProcessNode(aiNode * node, const aiScene * scene)
{
	for (int i = 0; i < node->mNumMeshes; ++i)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(ProcessMesh(mesh, scene));
	}

	for(int i = 0; i < node->mNumChildren; ++i)
	{
		ProcessNode(node->mChildren[i], scene);
	}
}

Mesh * MeshExporter::ProcessMesh(aiMesh * m, const aiScene * scene)
{
	const int vectorSize = 3;
	std::vector<Vertex> vertices;
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

	std::vector<unsigned int> indeces;
	for (int i = 0; i < m->mNumFaces; ++i)
	{
		auto face = m->mFaces[i];
		for (int j = 0; j < face.mNumIndices; ++j)
		{
			indeces.emplace_back(face.mIndices[j]);
		}
	}
	return new Mesh(vertices, indeces);
}
