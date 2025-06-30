#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"glm/gtc/type_ptr.hpp"
#include"VAO.h"
#include"EBO.h"
#include"shaderClass.h"
#include<map>

class Light : public drawableObject{

private:
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

	VAO vao;

	glm::vec3 Color;
	float Intensity = 1.0f;
	glm::vec3 Position;

	Shader* ownShader;

	std::map<int, defaultObject*>* shadersPtr;

	glm::mat4 model = glm::mat4(1.0f);

	Light(float size, glm::vec3 position, glm::vec3 color, float intensity, std::map<int, defaultObject*>* shaders_ptr, int shader);

	void Draw() override;
	void Translate(glm::vec3 vector);
	void MAJlight();
	void MAJlight(glm::vec3 newcolor);
	void Delete() override;

};