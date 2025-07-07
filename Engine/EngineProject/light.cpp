#include "light.h"

Light::Light(glm::vec3 position, glm::vec3 color, float intensity, std::map<int, defaultObject*>* shaders_ptr, int shaderProg) {

	Color = color;
	Intensity = intensity;
	shadersPtr = shaders_ptr;
	Light::shader = (Shader*)(*shadersPtr)[shaderProg];
	Position = position;

	vao.Bind();
	ebo.Bind();
	vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 3 * sizeof(GLfloat), (void*)0);
	vao.Unbind();
	ebo.Unbind();

	Translate(Position);
}

Light::Light(glm::vec3 position, glm::vec3 color, float intensity, glm::vec3 bottom, float inner, float outer, std::map<int, defaultObject*>* shaders_ptr, int shaderProg) {

	innerAngle = inner;
	outerAngle = outer;
	bottomVec = bottom;

	Color = color;
	Intensity = intensity;
	shadersPtr = shaders_ptr;
	Light::shader = (Shader*)(*shadersPtr)[shaderProg];
	Position = position;

	vao.Bind();
	ebo.Bind();
	vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 3 * sizeof(GLfloat), (void*)0);
	vao.Unbind();
	ebo.Unbind();

	Translate(Position);
}


void Light::Draw() {

	shader->Activate();

	glUniformMatrix4fv(glGetUniformLocation(shader->ID, "model"), 1, GL_FALSE, glm::value_ptr(model));

	vao.Bind();
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void Light::MAJlight() {
	std::map<int, defaultObject*>::iterator shaders_ite;
	for (shaders_ite = shadersPtr->begin(); shaders_ite != shadersPtr->end(); shaders_ite++) {
		Shader* crnt_shader_ptr = (Shader*)shaders_ite->second;
		crnt_shader_ptr->Activate();
		GLuint crntID = crnt_shader_ptr->ID;
		glUniform4f(glGetUniformLocation(crntID, "lightColor"), Color.x, Color.y, Color.z, 1.0f);
		glUniform3f(glGetUniformLocation(crntID, "lightPos"), Position.x, Position.y, Position.z);
		glUniform1f(glGetUniformLocation(crntID, "lightIntensity"), Intensity);
		glUniform3f(glGetUniformLocation(crntID, "bottomVec"), bottomVec.x, bottomVec.y, bottomVec.z);
		glUniform1f(glGetUniformLocation(crntID, "inner"), innerAngle);
		glUniform1f(glGetUniformLocation(crntID, "outer"), outerAngle);
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