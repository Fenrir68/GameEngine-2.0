#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;
layout (location = 2) in vec3 aNormal;

out vec2 TexPos;
out vec3 normal;
out vec3 crntPosition;

uniform mat4 model;
uniform mat4 mat4Cam;

void main()
{
	vec4 position = model * vec4(aPos, 1.0f);
	normal = normalize(mat3(model) * aNormal);
	crntPosition = position.xyz;

	TexPos = aTex;

	gl_Position = mat4Cam * position;
}