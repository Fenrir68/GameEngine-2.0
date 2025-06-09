#include"textureClass.h"

Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType) {

	type = texType;
	int widthImg, heightImg, numColCh;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

	glGenTextures(1, &ID);
	glActiveTexture(slot);
	glBindTexture(type, ID);

	glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(type, GL_TEXTURE_WRAP_R, GL_REPEAT);

	glTexImage2D(type, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);

	glGenerateMipmap(type);

	stbi_image_free(bytes);
	glBindTexture(type, 0);
}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit) {
	shader.Activate();
	glUniform1i(glGetUniformLocation(shader.ID, uniform) , unit);
}

void Texture::Bind() {
	glBindTexture(type, ID);
}

void Texture::Unbind() {
	glBindTexture(type, 0);
}

void Texture::Delete() {
	glDeleteTextures(1, &ID);
}