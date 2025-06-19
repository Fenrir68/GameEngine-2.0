#include "light.h"

Light::Light(glm::vec3 color, glm::vec3 position, float size, std::map<int, defaultObject*>* shaders_ptr, int shader) {

	Color = color;
	shadersPtr = shaders_ptr;
	ownShader = (Shader*)(*shadersPtr)[shader];

	for (int i = 0; i < 42; i++) {
		vertices[i] *= size;
	}

	vao = VAO();
	vbo = VBO(vertices, sizeof(vertices));

	vao.Bind();
	ebo.Bind();
	vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 3 * sizeof(GLfloat), (void*)0);
	vao.Unbind();
	ebo.Unbind();

	Translate(position);
}

void Light::Draw() {
	ownShader->Activate();

	glUniformMatrix4fv(glGetUniformLocation(ownShader->ID, "model"), 1, GL_FALSE, glm::value_ptr(model));

	vao.Bind();
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void Light::Translate(glm::vec3 vector) {
	model = glm::translate(model, vector);
}

void Light::MAJcolor() {
	std::map<int, defaultObject*>::iterator shaders_ite;
	for (shaders_ite = shadersPtr->begin(); shaders_ite != shadersPtr->end(); shaders_ite++) {
		Shader* crnt_shader_ptr = (Shader*)shaders_ite->second;
		crnt_shader_ptr->Activate();
		glUniform3f(glGetUniformLocation(crnt_shader_ptr->ID, "light"), Color.x, Color.y, Color.z);
	}
}

void Light::MAJcolor(glm::vec3 newcolor) {
	Color = newcolor;
	MAJcolor();
}

void Light::Delete() {
	ebo.Delete();
	vbo.Delete();
	vao.Delete();
}