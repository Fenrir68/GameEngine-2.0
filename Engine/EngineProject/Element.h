#pragma once
#include"Mesh.h"

#define Xaxis 0
#define Yaxis 1
#define Zaxis 2

class Element {
public:
	glm::vec3 position;
	glm::vec3 size;

	glm::mat4 model = glm::mat4(1.0f);
	float rotation[3] = { 0.0f, 0.0f, 0.0f };

	Shader* shaderProg;

	Mesh mesh;

	Element(Mesh mesh, glm::vec3 pos, glm::vec3 size, Shader* shader);
	void Draw();
	void addRotation(int ind, float value);
	void Scale(glm::vec3 size);
	void Translate(glm::vec3 dep);			//faire un relative translate(repère de l'objet) et un uni translate(repère global)
	void Rotate(float angle, int axis);		//faire un rotate qui prend direct un axe (pb: decomposer la rotation autour des axes x, y et z)

	void Delete();
};