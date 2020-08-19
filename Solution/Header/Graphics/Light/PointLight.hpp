#pragma once
#include "ObjectSystem/Actor.hpp"
#include "Graphics/Light/Light.hpp"

class Shader;

class PointLight : public Actor
{
public:
	PointLight(Engine* e);

	void AddLightToShader(Shader* shader, const int index);
	inline void SetLight(const Light& l) { light = l; }
	inline void SetConstant(const float c) { constant = c; }
	inline void SetLinear(const float l) { linear = l; }
	inline void SetQuadratic(const float q) { quadratic = q; }

private:
	Light light;
	float constant = 0;
	float linear = 0;
	float quadratic = 0;
};