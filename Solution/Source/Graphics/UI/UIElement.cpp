#include "Graphics/UI/UIElement.hpp"
#include "Engine/Engine.hpp"
#include <SDL.h>
#include "Graphics/Texture.hpp"
#include "Graphics/Shader.hpp"

void UIElement::DrawTexture(Shader* shader, Texture* texture, const Vector2& size, const Vector2& position, float scale)
{
	if (texture != nullptr) {
		Matrix4 scaleMat = Matrix4::CreateScale(
			static_cast<float>(size.x) * scale,
			static_cast<float>(size.y) * scale,
			1.0f);
		Matrix4 transMat = Matrix4::CreateTranslation(Vector3(position.x, position.y, 0));
		Matrix4 world = scaleMat * transMat;
		shader->SetMatrixUniform("uWorldTransform", world);
		texture->SetActive();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}
}
