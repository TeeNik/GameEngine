#pragma once
#include <unordered_map>
#include <string>
#include <vector>


class SpriteRendererComponent;
class Shader;
class Texture;
class Mesh;
class Engine;

class Renderer {
public:
	Renderer();
	~Renderer();

	bool Initialize(int screenWidth, int screenHeight);
	void Shitdown();
	void Unload();
	void Draw();

	void AddSprite(SpriteRendererComponent* sprite);
	void RemoveSprite(SpriteRendererComponent* sprite);
	
	void AddMeshComponent();
	void RemoveMeshComponent();

private:
	bool LoadShaders();
	void CreateSpriteVerts();
	void SetLightUniforms(Shader* shader);

	std::unordered_map<std::string, Texture*> textures;
	std::unordered_map<std::string, Mesh*> meshes;

	std::vector<SpriteRendererComponent*> spritesComponents;

	Engine* engine;
};