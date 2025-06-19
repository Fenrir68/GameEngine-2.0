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
	GLfloat vertices[42] =
	{
		0.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 0.0f
	};

	VBO vbo = VBO(0, 0);

	GLuint indices[36] =
	{
		0,1,2,
		1,2,3,

		2,3,7,
		3,7,8,

		3,4,8,
		4,8,9,

		4,5,9,
		5,9,10,

		5,6,10,
		6,10,11,

		10,11,12,
		11,12,13
	};
	EBO ebo = EBO(indices, sizeof(indices));

public:

	VAO vao;

	glm::vec3 Color;

	glm::vec3 Position;

	Shader* ownShader;

	std::map<int, defaultObject*>* shadersPtr;

	glm::mat4 model = glm::mat4(1.0f);

	Light(glm::vec3 color, glm::vec3 position, float size, std::map<int, defaultObject*>* shaders_ptr, int shader);

	void Draw() override;
	void Translate(glm::vec3 vector);
	void MAJcolor();
	void MAJcolor(glm::vec3 newcolor);
	void Delete() override;

};