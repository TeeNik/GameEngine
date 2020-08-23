#version 330

in vec2 fragTexCoord;
in vec3 fragNormal;
in vec3 fragWorldPos;

out vec4 outColor;

struct DirectionalLight
{
	vec3 direction;
	
	vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight
{
	vec3 position;
	float constant;
    float linear;
    float quadratic;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	vec3 baseColor;
	int hasDiffuse;
	int hasSpecular;
	float shininess;
};

#define MAX_LIGHTS 16

uniform int numOfPointLights;
uniform PointLight pointLights[MAX_LIGHTS];

uniform int numOfDirectionalLights;
uniform DirectionalLight directionalLights[MAX_LIGHTS];

uniform vec3 uCameraPos;

uniform Material material;

vec3 GetDiffuseColor()
{
	return texture(material.diffuse, fragTexCoord).rgb * material.hasDiffuse + (1-material.hasDiffuse) * material.baseColor;
}

vec3 GetSpecularColor()
{
	return texture(material.specular, fragTexCoord).rgb * material.hasSpecular + (1-material.hasDiffuse) * vec3(1,1,1);
}

vec3 CalcDirLight(DirectionalLight light, vec3 normal, vec3 viewDir)
{
	vec3 diffuseColor = GetDiffuseColor();
	vec3 specularColor = GetSpecularColor();

    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine results
    vec3 ambient = light.ambient * diffuseColor;
    vec3 diffuse = light.diffuse * diff * diffuseColor;
    vec3 specular = light.specular * spec * specularColor;
    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 diffuseColor = GetDiffuseColor();
	vec3 specularColor = GetSpecularColor();

    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // combine results
    vec3 ambient = light.ambient * diffuseColor;
    vec3 diffuse = light.diffuse * diff * diffuseColor;
    vec3 specular = light.specular * spec * specularColor;
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    
	return (ambient + diffuse + specular);
}

void main()
{
	vec3 result;

	vec3 norm = normalize(fragNormal);
	vec3 viewDir = normalize(uCameraPos - fragWorldPos);

	for(int i = 0; i < numOfPointLights; ++i)
		result += CalcDirLight(directionalLights[i], norm, viewDir);

	for(int i = 0; i < numOfPointLights; ++i)
		result += CalcPointLight(pointLights[i], norm, fragWorldPos, viewDir);

	outColor = vec4(result, 1.0f);
}