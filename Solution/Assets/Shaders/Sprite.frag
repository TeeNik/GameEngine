#version 330

in vec2 fragTexCoord;

out vec4 outColor;

uniform sampler2D uTexture;

uniform vec3 uFrameMin;
uniform vec3 uFrameMax;

void main()
{
	//vec2 frame = step(uFrameMin.xy, fragTexCoord);
	//frame *= vec2(1.0f, 1.0f) - step(uFrameMax.xy, fragTexCoord);
	//frame = frame.x * frame * frame.y;

	vec2 frame;
	frame.x = mix(uFrameMin.x, uFrameMax.x, fragTexCoord.x);
	frame.y = mix(uFrameMin.y, uFrameMax.y, fragTexCoord.y);

    outColor = texture(uTexture, frame);
}
