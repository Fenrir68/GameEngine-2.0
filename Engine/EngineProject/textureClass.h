#pragma once
#include"glad/glad.h"
#include"stb/stb_image.h"
#include"shaderClass.h"
#include"test.h"

class Texture: public test{
public:
	GLuint ID;
	GLenum type;
	Texture(const char* image, GLenum type, GLenum slot, GLenum format, GLenum pixelType);

	void texUnit(Shader& shader, const char* uniform, GLuint unit);
	void Bind();
	void Unbind();
	void Delete() override;
};