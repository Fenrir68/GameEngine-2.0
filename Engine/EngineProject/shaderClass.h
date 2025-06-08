#pragma once

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

std::string get_file_contents(const char* filename);

class Shader {
public:
	GLint ID;
	Shader(const char* vertexShader, const char* fragShader);

	void Activate();
	void Delete();
};