#include "ObjectSystem\AnimSpriteComponent.hpp"
#include "Graphics/Shader.hpp"
#include "Graphics/Texture.hpp"

void AnimSpriteComponent::SetSourceImage(const std::string path, int col, int row, int drawOrder)
{
	SetTexture(path, drawOrder);

	columns = col;
	rows = row;

	size.x = size.x / columns;
	size.y = size.y / rows;
}

void AnimSpriteComponent::Update(float deltaTime)
{
	SpriteRendererComponent::Update(deltaTime);

	currentFrame += (animFPS * deltaTime);
	while (currentFrame > rows * columns) {
		currentFrame = 0;
	}
	//currentFrame = static_cast<int>(currentFrame) % frames.size();
}

void AnimSpriteComponent::Draw(Shader* shader)
{
	Matrix4 scaleMat = Matrix4::CreateScale(size.x, size.y, 1);
	Matrix4 world = scaleMat * owner->GetWorldTransform();
	shader->SetMatrixUniform("uWorldTransform", world);

	int frame = static_cast<float>(currentFrame);

	float xMin = (frame % columns) / (float)columns;
	float xMax = Math::Min(1.0f, xMin + (1.0f/columns));

	float yMin = frame / columns / (float)rows;
	float yMax = Math::Min(1.0f, yMin + (1.0f / rows));
	
	shader->SetVectorUniform("uFrameMin", Vector3(xMin, yMin, 0));
	shader->SetVectorUniform("uFrameMax", Vector3(xMax, yMax, 0));

	texture->SetActive();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}
