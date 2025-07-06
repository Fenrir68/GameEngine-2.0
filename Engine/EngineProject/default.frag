#version 330 core

in vec2 TexPos;
in vec3 normal;
in vec3 crntPosition;

out vec4 FragColor;

uniform bool isTextured;

uniform sampler2D tex0;
uniform sampler2D tex1;

uniform vec3 camPos;

uniform vec3 lightPos;
uniform vec4 lightColor;
uniform float lightIntensity;
uniform float ambientLight;
uniform vec3 ownColor;

vec4 pointLight(){
	vec3 lightDirection = lightPos - crntPosition;
	float lightDist = length(lightDirection);
	lightDirection = normalize(lightDirection);
	float a = 0.1f;
	float b = 2.0f;
	float inten = lightIntensity / (a * lightDist * lightDist + b * lightDist + 1.0f);

	float dotProduct = dot(lightDirection, normal);
	float diffuse = max(dotProduct, 0.0f);

	float specLight = 0.5f;
	vec3 viewDirection = normalize(camPos - crntPosition);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(reflectionDirection, viewDirection), 0.0f), 8);
	float specular = specAmount * specLight;

	float lighting = diffuse * inten + ambientLight;

	if(isTextured){
		return (texture(tex0, TexPos) * lighting + texture(tex1, TexPos).r * specular) * lightColor;
	}
	return vec4(ownColor * (lighting + specular), 1.0f) * lightColor;
}

void main()
{
		FragColor = pointLight();
}