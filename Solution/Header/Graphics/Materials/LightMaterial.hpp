#pragma once
#include "Graphics/Materials/Material.hpp"

class LightMaterial : public Material
{
public:
	virtual void Use(Shader* shader) override;
};