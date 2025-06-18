#include"cube.h"
#include<iostream>

void cube::generalConstructor(int numCompo) {
	vao = VAO();
	vbo = VBO(vertices, sizeof(vertices));

	vao.Bind();
	ebo.Bind();
	vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)0);
	vao.LinkAttrib(vbo, 1, numCompo, GL_FLOAT, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	vao.Unbind();
	ebo.Unbind();

	Translate(cube::Position);
}

cube::cube(float side, glm::vec3 Position, Texture* texPtr, Shader* shader) {

	cube::side = side;
	cube::Position = Position;
	cube::shader = shader;

	tex = texPtr;
	(*tex).texUnit(*shader, "tex0", 0);

	for (int i = 0; i < 14; i++) {
		for (int j = 0; j < 3; j++) {
			vertices[6 * i + j] *= cube::side;
		}
	}
	generalConstructor(2);
}

cube::cube(float side, glm::vec3 Position, glm::vec3 color, Shader* shader) {

	cube::side = side;
	cube::Position = Position;
	cube::shader = shader;

	for (int i = 0; i < 14; i++) {
		for (int j = 0; j < 3; j++) {
			vertices[6 * i + j] *= cube::side;
			vertices[6 * i + j + 3] = color[j];
		}
	}

	generalConstructor(3);
}

void cube::Draw() {
	(*shader).Activate();

	glUniformMatrix4fv(glGetUniformLocation((*shader).ID, "model"), 1, GL_FALSE, glm::value_ptr(model));

	if (tex != NULL) {
		(*tex).Bind();
	}
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