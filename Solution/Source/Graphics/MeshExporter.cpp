#pragma once

#include "Graphics/MeshExporter.hpp"
#include "Graphics/Mesh.hpp"
#include "Graphics/SkeletalMesh.hpp"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "Engine/Engine.hpp"
#include "Graphics/Renderer.hpp"

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
		printf("ERROR NumMeshes > 1\n");
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
	//Mesh* mesh = new Mesh(m, scene);
	SkeletalMesh* mesh = new SkeletalMesh(m, scene, engine);
	mesh->SetupMesh();
	return mesh;
}

SkeletalMesh* MeshExporter::ProcessSkeletalMesh(aiMesh* mesh, const aiScene* scene)
{
	SkeletalMesh* sm = new SkeletalMesh(mesh, scene, engine);
	sm->SetupMesh();
	return sm;
}
