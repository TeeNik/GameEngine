#pragma once
#include <vector>

class PointLight;
class LightComponent;
class Shader;

class LightingSystem
{
public:
	void Update(Shader* shader);
	void RegisterLight(PointLight* light);

private:
	std::vector<PointLight> pointLights;

	void ProcessPointLights(Shader* shader);
};