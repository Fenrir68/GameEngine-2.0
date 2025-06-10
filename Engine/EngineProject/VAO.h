#pragma once
#include"VBO.h"

class VAO{
public:
	GLuint ID;
	VAO();
	void LinkAttrib(VBO& vbo, GLuint layout, GLuint numComponent, GLenum type, GLsizeiptr stride, void* offset);

	void Bind();
	void Unbind();
	void Delete();
};