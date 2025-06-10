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

//TODO ça serait cool de regrouper les class shader, texture et cube ensemble pour pouvoir toutes les supprimer d'un coup (supprimer la duplication de code à la fin)

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

	std::map<int, Shader*> shaderProgs;
	shaderProgs[0] = new Shader("default.vert", "default.frag");

	Camera camera = Camera(windowWidth, windowHeight, glm::vec3(0.0f, 0.0f, 2.5f), 45.0f, 0.1f, 20.0f, shaderProgs[0]);
	camera.Matrix();

	std::map<int, Texture*> textures;
	textures[0] = new Texture("brique.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	textures[1] = new Texture("cube_tex.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

	std::map<int, cube*> cubes;
	cubes[0] = new cube(1.0f, glm::vec3(0.0f, 0.0f, 0.0f), textures[1], shaderProgs[0]);
	cubes[1] = new cube(1.0f, glm::vec3(1.0f, 0.0f, 0.0f), textures[1], shaderProgs[0]);
	cubes[2] = new cube(1.0f, glm::vec3(0.0f, 1.0f, 0.0f), textures[1], shaderProgs[0]);
	cubes[3] = new cube(1.0f, glm::vec3(0.0f, 0.0f, 1.0f), textures[1], shaderProgs[0]);


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

		// Specify the color of the background
		//glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.Inputs(window);

		std::map<int, cube*>::iterator it;
		for (it = cubes.begin(); it != cubes.end(); it++) {
			(*(it->second)).Draw();
		}

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	};

	std::map<int, cube*>::iterator itc;
	std::cout << "cubes deleting...." << std::endl;
	for (itc = cubes.begin(); itc != cubes.end(); itc++) {
		std::cout << itc->first << std::endl;
		(*(itc->second)).Delete();
	}

	std::map<int, Texture*>::iterator itt;
	std::cout << "textures deleting...." << std::endl;
	for (itt = textures.begin(); itt != textures.end(); itt++) {
		std::cout << itt->first << std::endl;
		(*(itt->second)).Delete();
	}

	std::map<int, Shader*>::iterator its;
	std::cout << "shaders deleting...." << std::endl;
	for (its = shaderProgs.begin(); its != shaderProgs.end(); its++) {
		std::cout << its->first << std::endl;
		(*(its->second)).Delete();
	}

	glfwTerminate();
	return 0;
}