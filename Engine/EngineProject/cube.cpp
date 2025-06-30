#include"cube.h"
#include<iostream>

void Cube::general_constructor(float size, glm::vec3 Position, Shader* shader) {

	Cube::size = size;
	Cube::Position = Position;
	Cube::shader = shader;

	for (int i = 0; i < 24; i++) {
		for (int j = 0; j < 3; j++) {
			vertices[VERTEX_SIZE * i + j] *= Cube::size;
		}
	}
	vao = VAO();
	vbo = VBO(vertices, sizeof(vertices));

	vao.Bind();
	ebo.Bind();
	vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, VERTEX_SIZE * sizeof(GLfloat), (void*)0);
	vao.LinkAttrib(vbo, 1, 2, GL_FLOAT, VERTEX_SIZE * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	vao.LinkAttrib(vbo, 2, 3, GL_FLOAT, VERTEX_SIZE * sizeof(GLfloat), (void*)(5 * sizeof(GLfloat)));
	vao.Unbind();
	ebo.Unbind();

	Translate(Cube::Position);
}

Cube::Cube(float size, glm::vec3 Position, Texture* texPtr, Shader* shader) {

	tex = texPtr;
	tex->texUnit(*shader, "tex0", 0);

	general_constructor(size, Position, shader);
}

Cube::Cube(float size, glm::vec3 Position, glm::vec3 clr, Shader* shader) {

	Cube::color = clr;

	general_constructor(size, Position, shader);
}

void Cube::Draw() {
	shader->Activate();

	glUniformMatrix4fv(glGetUniformLocation(shader->ID, "model"), 1, GL_FALSE, glm::value_ptr(model));

	if (tex != NULL) {
		tex->Bind();
		glUniform1i(glGetUniformLocation(shader->ID, "isTextured"), GL_TRUE);
	}else {
		glUniform1i(glGetUniformLocation(shader->ID, "isTextured"), GL_FALSE);
		glUniform3fv(glGetUniformLocation(shader->ID, "ownColor"), 1, glm::value_ptr(color));
	}
	vao.Bind();
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void Cube::Rotate(float angle, glm::vec3 axe) {
	model = glm::rotate(model, glm::radians(angle), axe);
}

void Cube::Translate(glm::vec3 vector) {
	model = glm::translate(model, vector);
	Position += vector;
}

void Cube::goTo(glm::vec3 newPos) {
	model = glm::mat4(1.0f);
	Position = newPos;
	Translate(Position);
}

void Cube::Delete() {
	ebo.Delete();
	vbo.Delete();
	vao.Delete();
}