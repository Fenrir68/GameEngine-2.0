#pragma once

#include"VAO.h"
#include"EBO.h"
#include"defaultObject.h"
#include"shaderClass.h"
#include<map>

class Light : public drawableObject{

private:
	VAO vao;
	GLfloat vertices[24] =
	{
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, 0.5f,
		-0.5f, 0.5f, -0.5f,
		-0.5f, 0.5f, 0.5f,

		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, 0.5f,
		0.5f, 0.5f, -0.5f,
		0.5f, 0.5f, 0.5f
	};

	VBO vbo = VBO(0, 0);

	GLuint indices[36] =
	{
		0, 1, 2,
		1, 2, 3,

		4, 5, 0,
		5, 0, 1,

		6, 7, 4,
		7, 4, 5,

		2, 3, 6,
		3, 6, 7,

		0, 2, 4,
		2, 4, 6,

		1, 3, 5,
		3, 5, 7

	};
	EBO ebo = EBO(indices, sizeof(indices));

public:

	glm::vec3 Color;
	float Intensity = 1.0f;

	std::map<int, defaultObject*>* shadersPtr;
	Shader* shader;

	Light(float size, glm::vec3 position, glm::vec3 color, float intensity, std::map<int, defaultObject*>* shaders_ptr, int shader);

	void Draw() override;
	void MAJlight();
	void MAJlight(glm::vec3 newcolor);
	void Delete() override;

};