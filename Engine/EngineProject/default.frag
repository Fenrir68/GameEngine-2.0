#version 330 core

in vec2 TexPos;
in vec3 normal;
in vec3 crntPosition;

out vec4 FragColor;

uniform bool isTextured;

uniform sampler2D tex0;

uniform vec3 camPos;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform float lightIntensity;
uniform float ambientLight;
uniform vec3 ownColor;

vec4 pointLight(){
	vec3 lightDirection = lightPos - crntPosition;
	float lightDistance = length(lightDirection);

	float dotProduct = dot(normalize(lightDirection), normal);
	float diffuse = max(dotProduct, 0.0f) / lightDistance;

	float specLight = 0.75f;
	vec3 viewDirection = normalize(camPos - crntPosition);
	vec3 reflectionDirection = reflect(-normalize(lightDirection), normal);
	float specAmount = pow(max(dot(reflectionDirection, viewDirection), 0.0f), 8);
	float specular = specAmount * specLight;

	float lighting = diffuse * lightIntensity + ambientLight + specular;
	return vec4(lightColor * lighting, 1.0f);
}

void main()
{
	vec4 lightVec = pointLight();

	if (isTextured){
		FragColor = texture(tex0, TexPos) * lightVec;
	}else{
		FragColor = vec4(ownColor, 1.0f) * lightVec;
	}
}