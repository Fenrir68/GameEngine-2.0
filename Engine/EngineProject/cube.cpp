#include"cube.h"
#include<iostream>

cube::cube(float side, glm::vec3 Position, Texture* texPtr, Shader* shader) {

	cube::side = side;
	cube::Position = Position;
	cube::shader = shader;

	tex = texPtr;
	(*tex).texUnit(*shader, "tex0", 0);

	for (int i = 0; i < 14; i++) {
		for (int j = 0; j < 3; j++) {
			vertices[5 * i + j] *= cube::side;
		}
	}

	vao = VAO();
	vbo = VBO(vertices, sizeof(vertices));

	vao.Bind();
	ebo.Bind();
	vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 5*sizeof(GLfloat), (void*)0);
	vao.LinkAttrib(vbo, 1, 2, GL_FLOAT, 5 * sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));
	vao.Unbind();
	ebo.Unbind();

	Translate(cube::Position);
}

void cube::Draw() {
	(*shader).Activate();

	glUniformMatrix4fv(glGetUniformLocation((*shader).ID, "model"), 1, GL_FALSE, glm::value_ptr(model));

	(*tex).Bind();
	vao.Bind();
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void cube::Rotate(float angle, glm::vec3 axe) {
	model = glm::rotate(model, glm::radians(angle), axe);
}

void cube::Translate(glm::vec3 vector) {
	model = glm::translate(model, vector);
	Position += vector;
}

void cube::goTo(glm::vec3 newPos) {
	model = glm::mat4(1.0f);
	Position = newPos;
	Translate(Position);
}

void cube::Delete() {
	ebo.Delete();
	vbo.Delete();
	vao.Delete();
}