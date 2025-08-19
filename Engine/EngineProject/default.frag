#version 330 core

in vec3 crntPosition;
in vec3 normal;
in vec2 TexPos;

out vec4 FragColor;

uniform sampler2D diffuse0;
uniform sampler2D specular0;

uniform vec3 camPos;

uniform vec3 lightPos;
uniform vec4 lightColor;
uniform float lightIntensity;
uniform float ambientLight;

uniform vec3 bottomVec;
uniform float inner;
uniform float outer;

vec4 pointLight(){

	vec3 lightDirection = lightPos - crntPosition;
	float lightDist = length(lightDirection);
	lightDirection = normalize(lightDirection);
	float a = 0.1f;
	float b = 1.0f;
	float inten = lightIntensity / (a * lightDist * lightDist + b * lightDist + 1.0f);

	float dotProduct = dot(lightDirection, normal);
	float diffuse = max(dotProduct, 0.0f);

	float specLight = 0.2f;
	vec3 viewDirection = normalize(camPos - crntPosition);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(reflectionDirection, viewDirection), 0.0f), 16);
	float specular = specAmount * specLight;

	float lumens = diffuse * inten + ambientLight;

	return (texture(diffuse0, TexPos) * lumens + texture(specular0, TexPos).r * specular) * lightColor;
}

vec4 directionLight(){

	float diffuse = max(-dot(normalize(lightPos), normal), 0.0f);

	float lighting = diffuse * lightIntensity + ambientLight;

	return texture(diffuse0, TexPos) * lighting * lightColor;
}

vec4 spotLight(){

	vec3 lightDirection = lightPos - crntPosition;
	float lightDist = length(lightDirection);
	lightDirection = normalize(lightDirection);

	float angle = dot(-lightDirection, bottomVec);
	float inten = clamp((angle - outer) / (inner - outer), 0.0f, 1.0f);
	float dotProduct = dot(lightDirection, normal);
	float diffuse = max(dotProduct, 0.0f);

	float lighting = diffuse * (inten / (lightDist * lightDist)) + ambientLight;

	return texture(diffuse0, TexPos) * lighting * lightColor;
}

void main()
{
		FragColor = pointLight();
}