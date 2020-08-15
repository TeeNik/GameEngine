#pragma once
#include "Graphics/Materials/Material.hpp"

class Actor;

class LightMaterial : public Material
{
public:
	virtual void Use(Shader* shader) override;
	inline void SetData(Actor* lig, Actor* cam) { light = lig; camera = cam; }

private:
	Actor* light;
	Actor* camera;
};