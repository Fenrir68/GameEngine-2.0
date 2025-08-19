#include"Light.h"

Light::Light(Mesh mesh, glm::vec3 position, glm::vec3 size, glm::vec3 color, float intensity, std::map<int, Shader*>* shaders_ptr, int shaderProg) :
	Element(mesh, position, size, (*shaders_ptr)[shaderProg]) {

	Light::Color = color;
	Light::Intensity = intensity;
	Light::shadersPtr = shaders_ptr;
}

void Light::MAJlight() {
	std::map<int, Shader*>::iterator shaders_ite;
	for (shaders_ite = shadersPtr->begin(); shaders_ite != shadersPtr->end(); shaders_ite++) {
		shaders_ite->second->Activate();
		GLuint crntID = shaders_ite->second->ID;
		glUniform4f(glGetUniformLocation(crntID, "lightColor"), Color.x, Color.y, Color.z, 1.0f);
		glUniform3f(glGetUniformLocation(crntID, "lightPos"), Element::position.x, Element::position.y, Element::position.z);
		glUniform1f(glGetUniformLocation(crntID, "lightIntensity"), Intensity);
		glUniform3f(glGetUniformLocation(crntID, "bottomVec"), bottomVec.x, bottomVec.y, bottomVec.z);
		glUniform1f(glGetUniformLocation(crntID, "inner"), innerAngle);
		glUniform1f(glGetUniformLocation(crntID, "outer"), outerAngle);
	}
}

void Light::MAJlight(glm::vec3 newColor) {
	Color = newColor;
	MAJlight();
}

void Light::MAJlight(glm::vec3 bottom, float inner, float outer) {
	bottomVec = bottom;
	innerAngle = inner;
	outerAngle = outer;
	MAJlight();
}