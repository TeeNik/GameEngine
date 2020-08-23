#version 330

in vec2 fragTexCoord;
in vec3 fragNormal;
in vec3 fragWorldPos;

out vec4 outColor;

struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	vec3 baseColor;
	int hasDiffuse;
	int hasSpecular;
	float shininess;
};

uniform Material material;

void main()
{
	vec4 tex = texture(material.diffuse, fragTexCoord);
    outColor = vec4(1, 1, 1, 1);

	//outColor = texture(material.diffuse, fragTexCoord);
}