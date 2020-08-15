#pragma once 
#include "Graphics/Materials/Material.hpp"
#include "Math/Math.h"

class BaseColorMaterial : public Material
{
public:
	virtual void Use(Shader* shader) override;
	void SetColor(const Vector3& c) { color = c; }

private:
	Vector3 color;
};