#pragma once
#include"Mesh.h"

class Mesh_cube : public Mesh {
public:
	Vertex vertices[24] = {
		Vertex{glm::vec3(-0.5f, -0.5f, -0.5f),	glm::vec3(0.0f, 0.0f, -1.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(0.0f, 1.0f)},		//Back Face
		Vertex{glm::vec3(0.5f, -0.5f, -0.5f),	glm::vec3(0.0f, 0.0f, -1.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(0.25f, 1.0f)},
		Vertex{glm::vec3(-0.5f, 0.5f, -0.5f),	glm::vec3(0.0f, 0.0f, -1.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(0.0f, 0.67f)},
		Vertex{glm::vec3(0.5f, 0.5f, -0.5f),	glm::vec3(0.0f, 0.0f, -1.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(0.25f, 0.67f)},

		Vertex{glm::vec3(-0.5f, 0.5f, -0.5f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(0.0f, 0.67f)},		//Top Face
		Vertex{glm::vec3(0.5f, 0.5f, -0.5f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(0.25f, 0.67f)},
		Vertex{glm::vec3(-0.5f, 0.5f, 0.5f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(0.0f, 0.33f)},
		Vertex{glm::vec3(0.5f, 0.5f, 0.5f),		glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(0.25f, 0.33f)},

		Vertex{glm::vec3(0.5f, 0.5f, -0.5f),	glm::vec3(1.0f, 0.0f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(0.25f, 0.67f)},		//Right Face
		Vertex{glm::vec3(0.5f, 0.5f, 0.5f),		glm::vec3(1.0f, 0.0f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(0.25f, 0.33f)},
		Vertex{glm::vec3(0.5f, -0.5f, -0.5f),	glm::vec3(1.0f, 0.0f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(0.5f, 0.67f)},
		Vertex{glm::vec3(0.5f, -0.5f, 0.5f),	glm::vec3(1.0f, 0.0f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(0.5f, 0.33f)},

		Vertex{glm::vec3(0.5f, -0.5f, -0.5f),	glm::vec3(0.0f, -1.0f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(0.5f, 0.67f)},		//Bottom Face
		Vertex{glm::vec3(0.5f, -0.5f, 0.5f),	glm::vec3(0.0f, -1.0f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(0.5f, 0.33f)},
		Vertex{glm::vec3(-0.5f, -0.5f, -0.5f),	glm::vec3(0.0f, -1.0f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(0.75f, 0.67f)},
		Vertex{glm::vec3(-0.5f, -0.5f, 0.5f),	glm::vec3(0.0f, -1.0f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(0.75f, 0.33f)},

		Vertex{glm::vec3(-0.5f, -0.5f, -0.5f),	glm::vec3(-1.0f, 0.0f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(0.75f, 0.67f)},		//Left Face
		Vertex{glm::vec3(-0.5f, -0.5f, 0.5f),	glm::vec3(-1.0f, 0.0f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(0.75f, 0.33f)},
		Vertex{glm::vec3(-0.5f, 0.5f, -0.5f),	glm::vec3(-1.0f, 0.0f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 0.67f)},
		Vertex{glm::vec3(-0.5f, 0.5f, 0.5f),	glm::vec3(-1.0f, 0.0f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 0.33f)},

		Vertex{glm::vec3(-0.5f, -0.5f, 0.5f),	glm::vec3(0.0f, 0.0f, 1.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(0.75f, 0.33f)},		//Front Face
		Vertex{glm::vec3(-0.5f, 0.5f, 0.5f),	glm::vec3(0.0f, 0.0f, 1.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 0.33f)},
		Vertex{glm::vec3(0.5f, -0.5f, 0.5f),	glm::vec3(0.0f, 0.0f, 1.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(0.75f, 0.0f)},
		Vertex{glm::vec3(0.5f, 0.5f, 0.5f),		glm::vec3(0.0f, 0.0f, 1.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 0.0f)}
	};
	std::vector<Vertex> cube_vertVec = std::vector<Vertex>(vertices, vertices + 24);

	GLuint indices[36] = {
		0, 1, 2,
		1, 2, 3,

		4, 5, 6,
		5, 6, 7,

		8, 9, 10,
		9, 10, 11,

		12, 13, 14,
		13, 14, 15,

		16, 17, 18,
		17, 18, 19,

		20, 21, 22,
		21, 22, 23
	};
	std::vector<GLuint> cube_indVec = std::vector<GLuint>(indices, indices + 36);

	Mesh_cube(std::vector<Texture> texVec);
};