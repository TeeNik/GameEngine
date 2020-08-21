#include "Graphics\Light\Material.hpp"
#include "glew.h"

void Material::Use(Shader * shader)
{
	shader->SetIntUniform("material.diffuse", 0);
	shader->SetIntUniform("material.specular", 1);

	if (diffuse != nullptr) {
		diffuse->SetActive(GL_TEXTURE0);
		shader->SetIntUniform("hasDiffuse", 1);

		if (specular != nullptr)
		{
			specular->SetActive(GL_TEXTURE1);
			shader->SetIntUniform("hasSpecular", 1);
		}
	}
	else {
		shader->SetIntUniform("hasDiffuse", 0);
		shader->SetIntUniform("hasSpecular", 0);

		shader->SetVectorUniform("material.baseColor", baseColor);
	}

	
}
