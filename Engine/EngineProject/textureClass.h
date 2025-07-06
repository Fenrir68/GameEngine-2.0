#pragma once
#include"glad/glad.h"
#include"stb/stb_image.h"
#include"shaderClass.h"
#include"defaultObject.h"

class Texture: public defaultObject {
public:
	GLuint ID;
	GLenum type;
	GLuint unit;

	Texture* specMap = nullptr;

	Texture(const char* image, GLenum type, GLuint slot, GLenum format, GLenum pixelType, Texture* specMap);

	void texUnit(Shader& shader, const char* uniform, GLuint unit);
	void Bind();
	void Unbind();
	void Delete() override;
};