#pragma once
#include <string>
#include <vector>

class Shader;
class Mesh;
struct aiScene;
struct aiMesh;
struct aiNode;
class Engine;

class MeshExporter {
public:
	MeshExporter(Engine* engine);

	//refactor later
	std::vector<Mesh*>& LoadMeshes(const std::string& path);

	Mesh* LoadMesh(const std::string& path);

private:
	Engine* engine;
	std::vector<Mesh*> meshes;
	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh* ProcessMesh(aiMesh* mesh, const aiScene* scene);
};