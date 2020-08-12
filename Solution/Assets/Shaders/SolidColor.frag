#version 330

in vec2 fragTexCoord;
out vec4 outColor;

uniform vec3 color;

void main()
{
    outColor = vec4(color.x, color.y, color.z, 1);
}
