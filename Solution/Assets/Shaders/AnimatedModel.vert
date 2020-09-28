#version 430 core

uniform mat4 uWorldTransform;
uniform mat4 uViewProj;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoord;
layout(location = 3) in ivec4 bone_ids;     // INT pointer
layout(location = 4) in vec4 weights;

out vec2 fragTexCoord;

const int MAX_BONES = 100;
uniform mat4 bones[MAX_BONES];


uniform mat4 MVP;
uniform mat4 M_matrix;
uniform mat4 normals_matrix;

//void main()
//{
//	mat4 bone_transform = bones[bone_ids[0]] * weights[0];
//		bone_transform += bones[bone_ids[1]] * weights[1];
//		bone_transform += bones[bone_ids[2]] * weights[2];
//		bone_transform += bones[bone_ids[3]] * weights[3];
//			
//	vec4 boned_position = bone_transform * vec4(in_position, 1.0); // transformed by bones
//
//	normal = normalize(vec3(normals_matrix * (bone_transform * vec4(in_normal, 0.0))));
//
//	frag_pos = vec3(M_matrix * boned_position);
//	text_coords = in_text_coords;
//
//	gl_Position = MVP * boned_position;
//}

void main()
{
	mat4 bone_transform = bones[bone_ids[0]] * weights[0];
	bone_transform += bones[bone_ids[1]] * weights[1];
	bone_transform += bones[bone_ids[2]] * weights[2];
	bone_transform += bones[bone_ids[3]] * weights[3];

	vec4 boned_position = bone_transform * vec4(inPosition, 1.0);

	vec4 pos = vec4(inPosition, 1.0);
	gl_Position = pos * uWorldTransform * uViewProj;

	fragTexCoord = inTexCoord;
}