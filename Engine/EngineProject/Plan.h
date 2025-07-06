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

#define VERTEX_SIZE 8

class Plan : public drawableObject {
protected:

	VAO vao;

	GLfloat vertices[4 * VERTEX_SIZE] = {
	//		COORDINATES		//	TEXTURE		//		NORMAL
		-0.5f, 0.0f, 0.5f,		0.0f, 0.0f,		0.0f, 1.0f, 0.0f,
		-0.5f, 0.0f, -0.5f,		0.0f, 1.0f,		0.0f, 1.0f, 0.0f,
		0.5f, 0.0f, -0.5f,		1.0f, 1.0f,		0.0f, 1.0f, 0.0f,
		0.5f, 0.0f, 0.5f,		1.0f, 0.0f,		0.0f, 1.0f, 0.0f
	};
	VBO vbo = VBO(0, 0);

	GLuint indices[6] = {
		0, 1, 2,
		2, 3, 0
	};
	EBO ebo = EBO(indices, sizeof(indices));

	void generalConstructor(float size, glm::vec3 position, Shader* shader);
	
public:
	float size;

	glm::vec3 Position;
	Shader* shader;
	glm::vec3 color = glm::vec3(1.0f, 0.5f, 0.0f);

	Texture* tex = NULL;

	glm::mat4 model = glm::mat4(1.0f);

	Plan(float size, glm::vec3 position, Texture* texture, Shader* shader);
	Plan(float size, glm::vec3 position, glm::vec3 color, Shader* shader);

	void Rotate(float angle, glm::vec3 axe);
	void Translate(glm::vec3 vector);
	void goTo(glm::vec3 newPos);
	void Draw();
	void Delete();
};