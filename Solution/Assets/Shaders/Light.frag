#version 330

in vec2 fragTexCoord;
in vec3 fragNormal;
in vec3 fragWorldPos;

out vec4 outColor;

uniform sampler2D uTexture;

struct DirectionalLight
{
	vec3 direction;
	vec3 diffuseColor;
	vec3 specColor;
};

uniform vec3 uLightColor;
uniform vec3 uObjectColor;

uniform vec3 uCameraPos;
uniform float uSpecPower;
uniform vec3 uAmbientLight;
uniform DirectionalLight uDirLight;

void main()
{
	float ambientStrength = 0.1f;
	vec3 ambient = ambientStrength * uLightColor;
	vec3 result = ambient * uObjectColor;
	outColor = vec4(result, 1.0f);
}
