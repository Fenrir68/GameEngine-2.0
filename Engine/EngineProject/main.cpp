#include <iostream>
#include <map>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include"stb/stb_image.h"
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"glm/gtc/type_ptr.hpp"

#include"Camera.h"
#include"shaderClass.h"
#include"textureClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"cube.h"
#include"defaultObject.h"

#define SHADER_CODE 000
#define TEXTURE_CODE 100
#define CUBE_CODE 200


void add_element(std::map<int, defaultObject*>* dict, defaultObject* element, int type) {
	int n = 0;
	std::map<int, defaultObject*>::iterator it;
	for (it = dict->find(type); it != dict->end(); it++) {
		if (it->first > type + 99) { return; }
		n++;
	}
	(*dict)[type + n] = element;
}

int main() {
	glfwInit();

	//def la version de opengl utilisé
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//selectionne selement les modules les plus modernes (GLFW_OPENGL_COMPAT_PROFILE pour inclure les obsolètes)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	int windowWidth = 750;
	int windowHeight = 750;
	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "GameEngine", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	gladLoadGL();

	//bottom left -> top right
	glViewport(0, 0, windowWidth, windowHeight);

	std::map<int, defaultObject*> all; //000->099 = shader // 100->199 = textures // 200->299 = cube

	add_element(&all, new Shader("default.vert", "default.frag"), SHADER_CODE);

	add_element(&all, new Texture("brique.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE), TEXTURE_CODE);
	add_element(&all, new Texture("cube_tex.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE), TEXTURE_CODE);

	add_element(&all, new cube(1.0f, glm::vec3(0.0f, 0.0f, 0.0f), (Texture*)all[101], (Shader*)all[000]), CUBE_CODE);
	add_element(&all, new cube(1.0f, glm::vec3(1.0f, 0.0f, 0.0f), (Texture*)all[101], (Shader*)all[000]), CUBE_CODE);
	add_element(&all, new cube(1.0f, glm::vec3(0.0f, 1.0f, 0.0f), (Texture*)all[101], (Shader*)all[000]), CUBE_CODE);
	add_element(&all, new cube(1.0f, glm::vec3(0.0f, 0.0f, 1.0f), (Texture*)all[101], (Shader*)all[000]), CUBE_CODE);

	Camera camera = Camera(windowWidth, windowHeight, glm::vec3(0.0f, 0.0f, 2.5f), 45.0f, 0.1f, 20.0f, (Shader*)all[000]);
	camera.Matrix();

	//glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);

	glEnable(GL_DEPTH_TEST);


	int FPS = 30;
	float frq = 1.0f / FPS;
	double prevTime = glfwGetTime();

	while (!glfwWindowShouldClose(window))
	{
		double crntTime = glfwGetTime();
		while (crntTime - prevTime < frq) { crntTime = glfwGetTime(); }
		prevTime = crntTime;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.Inputs(window);

		std::map<int, defaultObject*>::iterator it0;
		for (it0 = all.find(200); it0 != all.end(); it0++) {
			if (it0->first > 299) { break; }
			((cube*)(it0->second))->Draw();
		}

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	};

	std::map<int, defaultObject*>::iterator it;
	for (it = all.begin(); it != all.end(); it++) {
		it->second->Delete();
	}

	glfwTerminate();
	return 0;
}