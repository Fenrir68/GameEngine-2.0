#version 330 core

in vec2 TexPos;
out vec4 FragColor;

uniform sampler2D tex0;
uniform vec3 light;

void main()
{
	FragColor = texture(tex0, TexPos) * vec4(light, 1.0f);
}