#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;

out vec2 TexPos;

uniform mat4 model;
uniform mat4 mat4Cam;

uniform vec3 LightPos;

void main()
{
	gl_Position = mat4Cam * model * vec4(aPos, 1.0f);
	TexPos = aTex;
}