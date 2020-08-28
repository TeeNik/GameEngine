#pragma once
#include "Graphics/Renderer.hpp"
#include "Graphics/Texture.hpp"
#include "Graphics/Mesh.hpp"
#include <algorithm>
#include "Graphics/Shader.hpp"
#include "Graphics/VertexArray.hpp"
#include "ObjectSystem/SpriteRendererComponent.hpp"
#include "ObjectSystem/MeshComponent.hpp"
#include <glew.h>
#include "Utils/Utils.hpp"
#include "Graphics/UI/Font.hpp"
#include "Graphics/Light/LightingSystem.hpp"

#include "Graphics/UI/Canvas.hpp"

Renderer::Renderer(Engine* engine) :
	engine(engine),
	spriteShader(nullptr),
	meshShader(nullptr),
	meshExporter(engine)
{
}

Renderer::~Renderer()
{
}

bool Renderer::Initialize(int sw, int sh)
{
	screenWidth = sw;
	screenHeight = sh;

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	window = SDL_CreateWindow("Window", 100, 100, screenWidth, screenHeight, SDL_WINDOW_OPENGL);
	if (!window)
	{
		printf("Failed to create window: %s", SDL_GetError());
		return false;
	}

	context = SDL_GL_CreateContext(window);
	lighting = new LightingSystem();

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		printf("Failed to initialize GLEW.");
		return false;
	}

	glGetError();

	if (!LoadShaders())
	{
		printf("Failed to load shaders.");
		return false;
	}
	CreateSpriteVerts();

	canvases.emplace_back(new Canvas(engine));

	return true;
}

void Renderer::Shutdown()
{
	delete lighting;

	for (auto texture : textures)
	{
		texture.second->Unload();
		delete texture.second;
	}
	textures.clear();

	for (auto mesh : meshes)
	{
		delete mesh.second;
	}
	meshes.clear();

	for (auto font : fonts) {
		font.second->Unload();
		delete font.second;
	}
	fonts.clear();

	for (auto canvas : canvases) {
		delete canvas;
	}
	canvases.clear();

	delete spriteVerts;

	for (auto shader : shaders)
	{
		shader.second->Unload();
		delete shader.second;
	}

	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
}

void Renderer::Draw()
{
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

	DrawMeshes();

	glDisable(GL_DEPTH_TEST);
	
	glEnable(GL_BLEND);
	glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

	spriteShader->SetActive();
	auto simpleVP = Matrix4::CreateSimpleViewProj(screenWidth, screenHeight);
	//auto add = Matrix4::CreateTranslation(Vector3(0, 100, 0));
	//simpleVP = add * simpleVP;
	spriteShader->SetMatrixUniform("uViewProj", simpleVP);

	spriteVerts->SetActive();
	for (auto sprite : sprites)
	{
		sprite->Draw(spriteShader);
	}

	for (auto canvas : canvases) {
		canvas->Draw(spriteShader);
	}

	SDL_GL_SwapWindow(window);
}

void Renderer::ProcessCanvasInput()
{
	for (auto canvas : canvases)
	{
		canvas->ProcessInput();
	}
}

void Renderer::AddSprite(SpriteRendererComponent* sprite)
{
	int myDrawOrder = sprite->GetDrawOrder();
	auto iter = sprites.begin();
	for (; iter != sprites.end(); ++iter)
	{
		if (myDrawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}

	sprites.insert(iter, sprite);
}

void Renderer::RemoveSprite(SpriteRendererComponent* sprite)
{
	auto iter = std::find(sprites.begin(), sprites.end(), sprite);
	sprites.erase(iter);
}

void Renderer::AddMeshComp(MeshComponent* mesh)
{
	meshComps.emplace_back(mesh);
}

void Renderer::RemoveMeshComp(MeshComponent* mesh)
{
	auto iter = std::find(meshComps.begin(), meshComps.end(), mesh);
	meshComps.erase(iter);
}

Texture* Renderer::GetTexture(const std::string& fileName)
{
	Texture* tex = nullptr;
	auto iter = textures.find(fileName);
	if (iter != textures.end())
	{
		tex = iter->second;
	}
	else
	{
		tex = new Texture();
		if (tex->Load(fileName))
		{
			textures.emplace(fileName, tex);
		}
		else
		{
			delete tex;
			tex = nullptr;
		}
	}
	return tex;
}

Mesh* Renderer::GetMesh(const std::string& fileName)
{
	Mesh* m = nullptr;
	auto iter = meshes.find(fileName);
	if (iter != meshes.end())
	{
		m = iter->second;
	}
	else
	{
		m = meshExporter.LoadMesh(fileName);
		if (m != nullptr)
		{
			meshes.emplace(fileName, m);
		}
	}
	return m;
}

Font* Renderer::GetFont(const std::string& fileName)
{
	auto iter = fonts.find(fileName);
	if (iter != fonts.end())
	{
		return iter->second;
	}
	else
	{
		Font* font = new Font(engine);
		if (font->Load(fileName))
		{
			fonts.emplace(fileName, font);
		}
		else
		{
			font->Unload();
			delete font;
			font = nullptr;
		}
		return font;
	}
}

bool Renderer::LoadShaders()
{
	spriteShader = GetShader("Sprite|Sprite");
	if (spriteShader == nullptr)
	{
		return false;
	}

	spriteShader->SetActive();

	Matrix4 viewProj = Matrix4::CreateSimpleViewProj(screenWidth, screenHeight);
	spriteShader->SetMatrixUniform("uViewProj", viewProj);

	meshShader = GetShader("BasicMesh|BasicMesh");
	if (meshShader == nullptr)
	{
		return false;
	}
	meshShader->SetActive();

	view = Matrix4::CreateLookAt(Vector3::Zero, Vector3::UnitX, Vector3::UnitZ);
	projection = Matrix4::CreatePerspectiveFOV(Math::ToRadians(70.0f), screenWidth, screenHeight, 25.0f, 10000.0f);
	meshShader->SetMatrixUniform("uViewProj", view * projection);
	return true;
}

void Renderer::DrawMeshes()
{
	for (auto mc : meshComps)
	{
		auto shaderName = mc->GetShaderName();
		if (shaderName != meshShader->GetName())
		{
			meshShader = GetShader(shaderName);
		}
		meshShader->SetActive();
		meshShader->SetMatrixUniform("uViewProj", view * projection);
		SetLightUniforms(meshShader);
		mc->Draw(meshShader);
	}
}

Shader* Renderer::GetShader(std::string name)
{
	auto iter = shaders.find(name);
	if (iter != shaders.end())
	{
		return iter->second;
	}
	else
	{
		Shader* shader = new Shader();

		std::string path = Utils::ContructPath("Shaders/");
		auto found = name.find_first_of('|');
		auto vert = path + name.substr(0, found) + ".vert";
		auto frag = path + name.substr(found+1, name.size()) + ".frag";

		if (shader->Load(name, vert, frag))
		{
			shaders.emplace(name, shader);
		}
		else
		{
			shader->Unload();
			delete shader;
			shader = nullptr;
		}
		return shader;
	}
}

void Renderer::CreateSpriteVerts()
{
	float vertices[] = {
		-0.5f, 0.5f, 0.f, 0.f, 0.f, 0.0f, 0.f, 0.f, // top left
		0.5f, 0.5f, 0.f, 0.f, 0.f, 0.0f, 1.f, 0.f, // top right
		0.5f,-0.5f, 0.f, 0.f, 0.f, 0.0f, 1.f, 1.f, // bottom right
		-0.5f,-0.5f, 0.f, 0.f, 0.f, 0.0f, 0.f, 1.f  // bottom left
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	spriteVerts = new VertexArray(vertices, 4, indices, 6);
}

void Renderer::SetLightUniforms(Shader* shader)
{
	Matrix4 invView = view;
	invView.Invert();
	shader->SetVectorUniform("uCameraPos", invView.GetTranslation());
	lighting->Update(shader);
	
	//shader->SetVectorUniform("uAmbientLight", ambientLight);
	//
	//shader->SetVectorUniform("uDirLight.direction", dirLight.direction);
	//shader->SetVectorUniform("uDirLight.diffuseColor", dirLight.diffuseColor);
	//shader->SetVectorUniform("uDirLight.specColor", dirLight.specColor);
}