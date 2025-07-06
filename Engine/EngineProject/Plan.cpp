#include"Plan.h"

void Plan::generalConstructor(float size, glm::vec3 position, Shader* shader) {
	Plan::size = size;
	Position = position;
	Plan::shader = shader;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			vertices[VERTEX_SIZE * i + j] *= size;
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

	Translate(position);
}

Plan::Plan(float size, glm::vec3 position, Texture* texture, Shader* shader) {
	tex = texture;
	texture->texUnit(*shader, "tex0", 0);

	generalConstructor(size, position, shader);
}

Plan::Plan(float size, glm::vec3 position, glm::vec3 color, Shader* shader) {
	Plan::color = color;

	generalConstructor(size, position, shader);
}

void Plan::Translate(glm::vec3 vector) {
	model = glm::translate(model, vector);
}

void Plan::goTo(glm::vec3 newPos) {
	model = glm::mat4(1.0f);
	Position = newPos;
	Translate(newPos);
}

void Plan::Rotate(float angle, glm::vec3 axe) {
	model = glm::rotate(model, glm::radians(angle), axe);
}

void Plan::Draw() {
	shader->Activate();

	glUniformMatrix4fv(glGetUniformLocation(shader->ID, "model"), 1, GL_FALSE, glm::value_ptr(model));

	if (tex != NULL) {
		tex->Bind();
		glUniform1i(glGetUniformLocation(shader->ID, "isTextured"), GL_TRUE);
	}
	else {
		glUniform1i(glGetUniformLocation(shader->ID, "isTextured"), GL_FALSE);
		glUniform3fv(glGetUniformLocation(shader->ID, "ownColor"), 1, glm::value_ptr(color));
	}
	vao.Bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Plan::Delete() {
	ebo.Delete();
	vbo.Delete();
	vao.Delete();
}