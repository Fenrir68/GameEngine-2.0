#pragma once

#include"Element.h"
#include<map>

class Light : public Element{

public:

	float innerAngle, outerAngle = 0.0f;
	glm::vec3 bottomVec = glm::vec3(0.0f);

	glm::vec3 Color;
	float Intensity = 1.0f;

	std::map<int, Shader*>* shadersPtr;

	Light(Mesh mesh, glm::vec3 position, glm::vec3 size, glm::vec3 color, float intensity, std::map<int, Shader*>* shaders_ptr, int shaderProg);	//point light

	void MAJlight();
	void MAJlight(glm::vec3 newcolor);
	void MAJlight(glm::vec3 bottom, float inner, float outer);
};