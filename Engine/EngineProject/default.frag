#version 330 core

in vec2 TexPos;
in vec3 normal;
in vec3 crntPosition;

out vec4 FragColor;

uniform bool isTextured;

uniform sampler2D tex0;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform float lightIntensity;
uniform float ambientLight;
uniform vec3 ownColor;

void main()
{
	vec3 lightDirection = lightPos - crntPosition;
	float lightDistance = length(lightDirection);

	float dotProduct = dot(normalize(lightDirection), normal);

	float diffuse = max(dotProduct, 0.0f) / lightDistance;
	float Brightness = diffuse * lightIntensity + ambientLight;

	if (isTextured){
		FragColor = texture(tex0, TexPos) * vec4(lightColor * Brightness, 1.0f);
	}else{
		FragColor = vec4(ownColor * lightColor * Brightness, 1.0f) ;
	}
}