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
#include "Graphics/SkeletalMesh.hpp"

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
	Mesh(const std::vector<Vertex>& v, const std::vector<unsigned int>& ind);
	Mesh(const aiMesh* m, const aiScene* scene);
	Mesh();
	~Mesh();
	
	//void SetTexture(Renderer* renderer, const std::string& path);
	
	void SetTexture(Texture* t);
	Texture* GetTexture(size_t index);

	inline float GetRadius() const { return radius; }
	inline float GetSpecPower() const { return specPower; }
	inline const AABB& GetBox() { return box; }

	virtual void Draw(Shader* shader);

	const aiScene* _scene;
	std::map<std::string, int> m_BoneMapping;
	std::vector<VertexBoneData> Bones;
	int m_NumBones = 0;
	std::vector<BoneMatrix> m_BoneInfo;

	Assimp::Importer importer;
	void LoadMesh(const std::string& path);
	void ProcessNode(aiNode* node, const aiScene* scene);
	void ProcessMesh(aiMesh* m, const aiScene* scene);
	void SetupMesh();
	class Engine* engine;

	void BoneTransform(float timeInSeconds, std::vector<aiMatrix4x4>& transforms);
	void ReadNodeHierarchy(float AnimationTime, const aiNode* pNode, const aiMatrix4x4 ParentTransform);
	const aiNodeAnim* FindNodeAnim(const aiAnimation* animation, const std::string p_node_name);
	int FindPosition(float p_animation_time, const aiNodeAnim* p_node_anim);
	int FindRotation(float p_animation_time, const aiNodeAnim* p_node_anim);
	int FindScaling(float p_animation_time, const aiNodeAnim* p_node_anim);
	aiVector3D CalcInterpolatedPosition(float p_animation_time, const aiNodeAnim* p_node_anim);
	aiQuaternion CalcInterpolatedRotation(float p_animation_time, const aiNodeAnim* p_node_anim);
	aiVector3D CalcInterpolatedScaling(float p_animation_time, const aiNodeAnim* p_node_anim);
	aiQuaternion nlerp(aiQuaternion a, aiQuaternion b, float blend);
	aiMatrix4x4 m_global_inverse_transform;
	static const int MAX_BONES = 100;
	GLuint m_bone_location[MAX_BONES];
	void printMatr(aiMatrix4x4 ai_matr);
	void readFromFile(std::vector<aiMatrix4x4>& transforms);
	Matrix4 toMat4(aiMatrix4x4 m);

private:
	void CalculateBox(const std::vector<Vertex>& v);

	AABB box;
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	unsigned int VAO, VBO, EBO, VBO_bones;

	std::vector<Texture*> textures;
	float radius;
	float specPower;
};