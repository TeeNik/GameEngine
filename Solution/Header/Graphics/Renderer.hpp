#pragma once


class SpriteRendererComponent;

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

};