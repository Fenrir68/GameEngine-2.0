#pragma once
#include <iostream>
#include <vector>

#include"Camera.h"
#include"textureClass.h"
#include"VAO.h"
#include"EBO.h"

class Mesh {
protected:

	void Mesh_ctor();	//make vbo, ebo, and link vao layout

public:
	std::vector <Vertex> vertices;
	std::vector <GLuint> indices;
	std::vector <Texture> textures;

	VAO vao;
	Mesh();
	Mesh(std::vector<Vertex> vertices, 
		std::vector <GLuint> indices, 
		std::vector <Texture> textures);	//Link vectors

	void Draw(Shader& shader, glm::mat4 matrix = glm::mat4(1.0f));
	void Delete();
};