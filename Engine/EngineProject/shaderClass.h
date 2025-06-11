#pragma once

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>
#include"test.h"

std::string get_file_contents(const char* filename);

class Shader: public test{
public:
	GLint ID;
	Shader(const char* vertexShader, const char* fragShader);

	void Activate();
	void Delete() override;
};