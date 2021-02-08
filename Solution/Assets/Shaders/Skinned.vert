#version 330

const int MAX_BONES = 100;

uniform mat4 uWorldTransform;
uniform mat4 uViewProj;
uniform mat4 uBones[MAX_BONES];

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoord;
layout(location = 3) in uvec4 inSkinBones;
layout(location = 4) in vec4 inSkinWeights;

out vec2 fragTexCoord;
out vec3 fragNormal;
out vec3 fragWorldPos;

void main()
{
	vec4 pos = vec4(inPosition, 1.0);
	vec4 boneTransform = (pos * uBones[inSkinBones[0]]) * inSkinWeights[0];
		boneTransform += (pos * uBones[inSkinBones[1]]) * inSkinWeights[1];
		boneTransform += (pos * uBones[inSkinBones[2]]) * inSkinWeights[2];
		boneTransform += (pos * uBones[inSkinBones[3]]) * inSkinWeights[3];

	boneTransform = boneTransform * uWorldTransform;
	fragWorldPos = pos.xyz;
	gl_Position = boneTransform * uViewProj;

	fragNormal = (boneTransform * vec4(inNormal, 0.0f) * uWorldTransform).xyz;
	fragTexCoord = inTexCoord;
}
