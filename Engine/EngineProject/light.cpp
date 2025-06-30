#include "light.h"

Light::Light(float size, glm::vec3 position, glm::vec3 color, float intensity, std::map<int, defaultObject*>* shaders_ptr, int shader) {

	Color = color;
	Intensity = intensity;
	shadersPtr = shaders_ptr;
	ownShader = (Shader*)(*shadersPtr)[shader];
	Position = position;

	for (int i = 0; i < 24; i++) {
		vertices[i] *= size;
	}

	vao = VAO();
	vbo = VBO(vertices, sizeof(vertices));

	vao.Bind();
	ebo.Bind();
	vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 3 * sizeof(GLfloat), (void*)0);
	vao.Unbind();
	ebo.Unbind();

	Translate(Position);
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

void Light::MAJlight() {
	std::map<int, defaultObject*>::iterator shaders_ite;
	for (shaders_ite = shadersPtr->begin(); shaders_ite != shadersPtr->end(); shaders_ite++) {
		Shader* crnt_shader_ptr = (Shader*)shaders_ite->second;
		crnt_shader_ptr->Activate();
		GLuint crntID = crnt_shader_ptr->ID;
		glUniform3f(glGetUniformLocation(crntID, "lightColor"), Color.x, Color.y, Color.z);
		glUniform3f(glGetUniformLocation(crntID, "lightPos"), Position.x, Position.y, Position.z);
		glUniform1f(glGetUniformLocation(crntID, "lightIntensity"), Intensity);
	}
}

void Light::MAJlight(glm::vec3 newcolor) {
	Color = newcolor;
	MAJlight();
}

void Light::Delete() {
	ebo.Delete();
	vbo.Delete();
	vao.Delete();
}