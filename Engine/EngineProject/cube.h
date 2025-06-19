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

class cube: public drawableObject {
protected:
	VAO vao;

	//TODO pour les coo de tex peut-être passer sur un sprite carré pour avoir des coo qui tombe pile ( pas de 1/3 comme là )

	GLfloat vertices[84] =
	{
		0.0f, 1.0f, 1.0f,		0.0f, 1.0f,		0.0f,//A
		1.0f, 1.0f, 1.0f,		0.25f, 1.0f,	0.0f,//B
		0.0f, 0.0f, 1.0f,		0.0f, 0.67f,	0.0f,//C
		1.0f, 0.0f, 1.0f,		0.25f, 0.67f,	0.0f,//D
		1.0f, 1.0f, 1.0f,		0.5f, 0.67f,	0.0f,//E
		0.0f, 1.0f, 1.0f,		0.75f, 0.67f,	0.0f,//F
		0.0f, 0.0f, 1.0f,		1.0f, 0.67f,	0.0f,//G
		0.0f, 0.0f, 0.0f,		0.0f, 0.33f,	0.0f,//H
		1.0f, 0.0f, 0.0f,		0.25f, 0.33f,	0.0f,//I
		1.0f, 1.0f, 0.0f,		0.5f, 0.33f,	0.0f,//J
		0.0f, 1.0f, 0.0f,		0.75f, 0.33f,	0.0f,//K
		0.0f, 0.0f, 0.0f,		1.0f, 0.33f,	0.0f,//L
		1.0f, 1.0f, 0.0f,		0.75f, 0.0f,	0.0f,//M
		1.0f, 0.0f, 0.0f,		1.0f, 0.0f,		0.0f//N
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

	void generalConstructor(int numCompo);

public:
	
	float side;

	glm::vec3 Position;

	Shader* shader;

	Texture* tex = NULL;

	glm::mat4 model = glm::mat4(1.0f);

	cube(float side, glm::vec3 Position, Texture* texPtr, Shader* shader);
	cube(float side, glm::vec3 Position, glm::vec3 color, Shader* shader);

	void Rotate(float angle, glm::vec3 axe);
	void Translate(glm::vec3 vector);
	void goTo(glm::vec3 newPos);
	void Draw() override;
	void Delete() override;
};