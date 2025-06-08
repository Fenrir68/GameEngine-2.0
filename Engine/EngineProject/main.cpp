#include <iostream>
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


int main() {
	glfwInit();

	//def la version de opengl utilisé
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//selectionne selement les modules les plus modernes (GLFW_OPENGL_COMPAT_PROFILE pour inclure les obsolètes)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	int windowWidth = 750;
	int windowHeight = 750;
	float screenRatio = (float)windowWidth / windowHeight;
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

	Shader shaderProg = Shader("default.vert", "default.frag");

	Camera camera = Camera(windowWidth, windowHeight, glm::vec3(0.0f, 0.0f, 2.5f), &shaderProg);
	camera.Matrix(45.0f, 0.1f, 20.0f, shaderProg, "mat4Cam");

	Texture briqueTex = Texture("brique.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	Texture defaultTex = Texture("cube_tex.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

	cube cub0 = cube(0.5f, glm::vec3(0.0f, 0.0f, 0.0f) , &briqueTex, &shaderProg);
	cube cub1 = cube(0.5f, glm::vec3(0.5f, 0.5f, 0.5f), &defaultTex, &shaderProg);

	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);

	glEnable(GL_DEPTH_TEST);

	int FPS = 120;
	float frq = 1.0f / FPS;
	double prevTime = glfwGetTime();

	int a = 0;
	bool isTurning = false;


	while (!glfwWindowShouldClose(window))
	{
		double crntTime = glfwGetTime();
		while (crntTime - prevTime < frq) { crntTime = glfwGetTime(); }
		prevTime = crntTime;

		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use

		camera.Inputs(window);

		cub0.Draw();
		cub1.Draw();

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	};
	cub0.Delete();
	cub1.Delete();
	briqueTex.Delete();
	defaultTex.Delete();
	shaderProg.Delete();

	glfwTerminate();
	return 0;
}