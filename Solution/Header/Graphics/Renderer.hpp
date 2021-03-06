#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <SDL.h>
#include <Math\Math.h>
#include "Graphics/MeshExporter.hpp"

class SpriteRendererComponent;
class MeshComponent;
class Shader;
class Texture;
class Mesh;
class Engine;
class VertexArray;
class Font;
class Canvas;
class LightingSystem;

struct aiScene;
struct aiMesh;

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

	void Draw();
	void ProcessCanvasInput();

	void AddSprite(SpriteRendererComponent* sprite);
	void RemoveSprite(SpriteRendererComponent* sprite);

	void AddMeshComp(MeshComponent* mesh);
	void RemoveMeshComp(MeshComponent* mesh);

	Texture* GetTexture(const std::string& fileName);
	Texture* GetTexture(const aiScene* scene, const aiMesh* mesh);
	Mesh* GetMesh(const std::string& fileName);

	inline void SetViewMatrix(const Matrix4& v) { view = v; }

	inline void SetAmbientLight(const Vector3& ambient) { ambientLight = ambient; }
	inline DirectionalLight& GetDirectionalLight() { return dirLight; }

	inline float GetScreenWidth() const { return static_cast<float>(screenWidth); }
	inline float GetScreenHeight() const { return static_cast<float>(screenHeight); }
	inline LightingSystem* GetLighting() const { return lighting; }

	Font* GetFont(const std::string& fileName);
private:
	bool LoadShaders();
	void CreateSpriteVerts();
	void SetLightUniforms(class Shader* shader);

	std::unordered_map<std::string, class Texture*> textures;
	std::unordered_map<std::string, class Mesh*> meshes;

	std::vector<SpriteRendererComponent*> sprites;
	std::vector<MeshComponent*> meshComps;

	Engine* engine;
	MeshExporter meshExporter;

	Shader* spriteShader;
	VertexArray* spriteVerts;
	std::unordered_map<std::string, Font*> fonts;
	std::vector<Canvas*> canvases;

	void DrawMeshes();
	Shader* meshShader;
	std::unordered_map <std::string, Shader*> shaders;
	Shader* GetShader(std::string name);

	Matrix4 view;
	Matrix4 projection;
	
	int screenWidth;
	int screenHeight;

	LightingSystem* lighting;

	Vector3 ambientLight;
	DirectionalLight dirLight;

	SDL_Window* window;
	SDL_GLContext context;
};