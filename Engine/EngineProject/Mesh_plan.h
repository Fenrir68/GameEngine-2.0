#pragma once
#include"Mesh.h"

class Mesh_plan : public Mesh {
public:
	Vertex plan_vertices[4] = {
		Vertex{glm::vec3(-0.5f, 0.0f, -0.5f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(0.0f, 1.0f)},
		Vertex{glm::vec3(-0.5f, 0.0f, 0.5f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(0.0f, 0.0f)},
		Vertex{glm::vec3(0.5f, 0.0f, -0.5f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f)},
		Vertex{glm::vec3(0.5f, 0.0f, 0.5f),		glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	 glm::vec2(1.0f, 0.0f)}
	};
	std::vector<Vertex> plan_vertVec = std::vector<Vertex>(plan_vertices, plan_vertices + 4);

	GLuint plan_indices[6] = {
		0, 1, 2,
		1, 2, 3
	};
	std::vector<GLuint> plan_indVec = std::vector<GLuint>(plan_indices, plan_indices + 6);
	
	Mesh_plan(std::vector<Texture> texVec);
};