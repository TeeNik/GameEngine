#include "Engine/Engine.hpp"
#include "Graphics/Renderer.hpp"
#include "Graphics/UI/Canvas.hpp"
#include "Graphics/Texture.hpp"
#include "Graphics/Shader.hpp"
#include "Utils/Utils.hpp"
#include "Graphics/UI/Font.hpp"

Canvas::Canvas(Engine* e) : engine(e)
{
	font = e->GetRenderer()->GetFont(Utils::ContructPath("Fonts/Ubuntu-Bold.ttf"));
	text = font->RenderText("Some text");
}

Canvas::~Canvas()
{
}

void Canvas::Update(float deltaTime)
{
}

void Canvas::Draw(Shader* shader)
{
	DrawTexture(shader, text, Vector2(0, 0), 1);
}

void Canvas::DrawTexture(Shader* shader, Texture* texture, const Vector2& offset, float scale)
{
	Matrix4 scaleMat = Matrix4::CreateScale(
		static_cast<float>(texture->GetWidth()) * scale,
		static_cast<float>(texture->GetHeight()) * scale,
		1.0f);
	Matrix4 transMat = Matrix4::CreateTranslation(Vector3(offset.x, offset.y, 0));
	Matrix4 world = scaleMat * transMat;
	shader->SetMatrixUniform("uWorldTransform", world);
	texture->SetActive();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}
