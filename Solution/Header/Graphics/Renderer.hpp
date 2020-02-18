#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <SDL.h>
#include <Math\Math.h>


class SpriteRendererComponent;
class MeshComponent;
class Shader;
class Texture;
class Mesh;
class Engine;
class VertexArray;

struct DirectionalLight
{
	Vector3 direction;
	Vector3 diffuseColor;
	Vector3 specColor;
};

class Renderer {
public:
	Renderer(Engine* game);
	~Renderer();

	bool Initialize(int sw, int sh);
	void Shutdown();
	void UnloadData();

	void Draw();

	void AddSprite(SpriteRendererComponent* sprite);
	void RemoveSprite(SpriteRendererComponent* sprite);

	void AddMeshComp(MeshComponent* mesh);
	void RemoveMeshComp(MeshComponent* mesh);

	class Texture* GetTexture(const std::string& fileName);
	class Mesh* GetMesh(const std::string& fileName);

	inline void SetViewMatrix(const Matrix4& v) { view = v; }

	inline void SetAmbientLight(const Vector3& ambient) { ambientLight = ambient; }
	inline DirectionalLight& GetDirectionalLight() { return dirLight; }

	float GetScreenWidth() const { return screenWidth; }
	float GetScreenHeight() const { return screenHeight; }
private:
	bool LoadShaders();
	void CreateSpriteVerts();
	void SetLightUniforms(class Shader* shader);

	std::unordered_map<std::string, class Texture*> textures;
	std::unordered_map<std::string, class Mesh*> meshes;

	std::vector<SpriteRendererComponent*> sprites;
	std::vector<MeshComponent*> meshComps;

	Engine* engine;

	Shader* spriteShader;
	VertexArray* spriteVerts;

	Shader* meshShader;

	Matrix4 view;
	Matrix4 projection;
	
	int screenWidth;
	int screenHeight;

	Vector3 ambientLight;
	DirectionalLight dirLight;

	SDL_Window* window;
	SDL_GLContext context;
};