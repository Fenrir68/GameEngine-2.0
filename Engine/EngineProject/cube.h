#pragma once
#include"cstdlib"
#include"glad/glad.h"
#include"GLFW/glfw3.h"
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"glm/gtc/type_ptr.hpp"

#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"textureClass.h"
#include"shaderClass.h"
#include"defaultObject.h"

class Cube: public drawableObject {
protected:
	VAO vao;

	//TODO pour les coo de tex peut-être passer sur un sprite carré pour avoir des coo qui tombe pile ( pas de 1/3 comme là )

	GLfloat vertices[120] =
	{
		//		COORDONATE		//		TEXTURE

			0.0f, 1.0f, 1.0f,		0.0f, 1.0f,
			0.0f, 0.0f, 1.0f,		0.0f, 0.67f,
			1.0f, 1.0f, 1.0f,		0.25f, 1.0f,
			1.0f, 0.0f, 1.0f,		0.25f, 0.67f,

			0.0f, 0.0f, 1.0f,		0.0f, 0.67f,
			0.0f, 0.0f, 0.0f,		0.0f, 0.33f,
			1.0f, 0.0f, 1.0f,		0.25f, 0.67f,
			1.0f, 0.0f, 0.0f,		0.25f, 0.33f,

			1.0f, 0.0f, 1.0f,		0.25f, 0.67f,
			1.0f, 0.0f, 0.0f,		0.25f, 0.33f,
			1.0f, 1.0f, 1.0f,		0.5f, 0.67f,
			1.0f, 1.0f, 0.0f,		0.5f, 0.33f,

			1.0f, 1.0f, 1.0f,		0.5f, 0.67f,
			1.0f, 1.0f, 0.0f,		0.5f, 0.33f,
			0.0f, 1.0f, 1.0f,		0.75f, 0.67f,
			0.0f, 1.0f, 0.0f,		0.75f, 0.33f,

			0.0f, 1.0f, 1.0f,		0.75f, 0.67f,
			0.0f, 1.0f, 0.0f,		0.75f, 0.33f,
			0.0f, 0.0f, 1.0f,		1.0f, 0.67f,
			0.0f, 0.0f, 0.0f,		1.0f, 0.33f,

			0.0f, 0.0f, 0.0f,		1.0f, 0.33f,
			0.0f, 1.0f, 0.0f,		0.75f, 0.33f,
			1.0f, 0.0f, 0.0f,		1.0f, 0.0f,
			1.0f, 1.0f, 0.0f,		0.75f, 0.0f

		};

	VBO vbo = VBO(0, 0);

	GLuint indices[36] =
	{
		0,1,2,
		1,2,3,

		4,5,6,
		5,6,7,

		8,9,10,
		9,10,11,

		12,13,14,
		13,14,15,

		16,17,18,
		17,18,19,

		20,21,22,
		21,22,23
	};
	EBO ebo = EBO(indices, sizeof(indices));

	void general_constructor(float size, glm::vec3 Position, Shader* shader);

public:
	
	float size;

	glm::vec3 Position;

	Shader* shader;
	glm::vec3 color = glm::vec3(0.8f, 0.2f, 1.0f);

	Texture* tex = NULL;

	glm::mat4 model = glm::mat4(1.0f);

	Cube(float size, glm::vec3 Position, Texture* texPtr, Shader* shader);
	Cube(float size, glm::vec3 Position, glm::vec3 clr, Shader* shader);

	void Rotate(float angle, glm::vec3 axe);
	void Translate(glm::vec3 vector);
	void goTo(glm::vec3 newPos);
	void Draw() override;
	void Delete() override;
};