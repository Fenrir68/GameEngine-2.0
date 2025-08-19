#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec2 aTex;

out vec3 crntPosition;
out vec3 normal;
out vec2 TexPos;

uniform mat4 model;
uniform mat4 mat4Cam;

void main()
{
	vec4 position = model * vec4(aPos, 1.0f);
	normal = normalize(mat3(model) * aNormal);
	crntPosition = position.xyz;

	TexPos = mat2(0.0f, -1.0f, 1.0f, 0.0f) * aTex;

	gl_Position = mat4Cam * position;
}