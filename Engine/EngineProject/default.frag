#version 330 core

in vec2 TexPos;

out vec4 FragColor;

uniform bool isTextured;

uniform sampler2D tex0;
uniform vec3 light;
uniform vec3 color;

void main()
{
	if (isTextured){
		FragColor = texture(tex0, TexPos) * vec4(light, 1.0f);
	}else{
		FragColor = vec4(color * light, 1.0f);
	}
}