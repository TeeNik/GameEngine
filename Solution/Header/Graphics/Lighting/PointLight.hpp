#pragma once
#include "ObjectSystem/Actor.hpp"
#include "ObjectSystem/LightComponent.hpp"
#include "Graphics/Lighting/Light.hpp"

class PointLight : public Actor
{

	class PointLightComponent : public LightComponent
	{
	public:
		PointLightComponent(Actor* a) : LightComponent(a) {}

		virtual void ProcessLight() override;
	};

public:
	PointLight(Engine* e);

	void AddLightToShader(Shader* shader, const int index);
	inline void SetLight(const Light& l) { light = l; }
	inline void SetConstant(const float c) { constant = c; }
	inline void SetLinear(const float l) { linear = l; }
	inline void SetQuadratic(const float q) { quadratic = q; }

private:
	Light light;
	float constant;
	float linear;
	float quadratic;
};