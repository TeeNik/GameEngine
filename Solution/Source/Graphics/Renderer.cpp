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

Renderer::Renderer(Engine* engine) :
	engine(engine),
	spriteShader(nullptr),
	meshShader(nullptr)
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

	return true;
}

void Renderer::Shutdown()
{
	delete spriteVerts;
	spriteShader->Unload();
	delete spriteShader;
	meshShader->Unload();
	delete meshShader;
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
}

void Renderer::UnloadData()
{
	for (auto texture : textures)
	{
		texture.second->Unload();
		delete texture.second;
	}
	textures.clear();

	for (auto mesh : meshes)
	{
		mesh.second->Unload();
		delete mesh.second;
	}
	meshes.clear();
}

void Renderer::Draw()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	
	meshShader->SetActive();
	meshShader->SetMatrixUniform("uViewProj", view * projection);
	
	SetLightUniforms(meshShader);
	for (auto mc : meshComps)
	{
		mc->Draw(meshShader);
	}

	glDisable(GL_DEPTH_TEST);
	
	glEnable(GL_BLEND);
	glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

	spriteShader->SetActive();
	spriteVerts->SetActive();
	for (auto sprite : sprites)
	{
		sprite->Draw(spriteShader);
	}

	SDL_GL_SwapWindow(window);
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
		m = new Mesh();
		if (m->Load(fileName, this))
		{
			meshes.emplace(fileName, m);
		}
		else
		{
			delete m;
			m = nullptr;
		}
	}
	return m;
}

bool Renderer::LoadShaders()
{
	spriteShader = new Shader();
	if (!spriteShader->Load("../Solution/Assets/Shaders/Sprite.vert", "../Solution/Assets/Shaders/Sprite.frag"))
	{
		return false;
	}

	spriteShader->SetActive();

	Matrix4 viewProj = Matrix4::CreateSimpleViewProj(screenWidth, screenHeight);
	spriteShader->SetMatrixUniform("uViewProj", viewProj);

	meshShader = new Shader();
	if (!meshShader->Load("../Solution/Assets/Shaders/Phong.vert", "../Solution/Assets/Shaders/Phong.frag"))
	{
		return false;
	}

	meshShader->SetActive();

	view = Matrix4::CreateLookAt(Vector3::Zero, Vector3::UnitX, Vector3::UnitZ);
	projection = Matrix4::CreatePerspectiveFOV(Math::ToRadians(70.0f), screenWidth, screenHeight, 25.0f, 10000.0f);
	meshShader->SetMatrixUniform("uViewProj", view * projection);
	return true;
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
	
	shader->SetVectorUniform("uAmbientLight", ambientLight);
	
	shader->SetVectorUniform("uDirLight.direction", dirLight.direction);
	shader->SetVectorUniform("uDirLight.diffuseColor", dirLight.diffuseColor);
	shader->SetVectorUniform("uDirLight.specColor", dirLight.specColor);
}