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
uniform vec3 uLightPos;
uniform vec3 uCameraPos;

uniform float uSpecPower;
uniform vec3 uAmbientLight;
uniform DirectionalLight uDirLight;

void main()
{
	float ambientStrength = 0.1f;
	vec3 ambient = ambientStrength * uLightColor;

	vec3 norm = normalize(fragNormal);
	vec3 lightDir = normalize(uLightPos - fragWorldPos);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = diff * uLightColor;

	float specularStrength = 0.5f;
	vec3 viewDir = normalize(uCameraPos - fragWorldPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	int shininess = 32;
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), shininess);
	vec3 specular = specularStrength * spec * uLightColor;

	vec3 result = (ambient + diffuse + specular) * uObjectColor;
	outColor = vec4(result, 1.0f);
}
