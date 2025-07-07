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
#include"Plan.h"
#include"light.h"
#include"defaultObject.h"
#include"dictManager.h"

void MAJlightcolor(std::map<int, std::map<int, defaultObject*>*>* dict, int light) {
	((Light*)(*(*dict)[LIGHT_TYPE])[light])->MAJlight();
}

void MAJlightcolor(std::map<int, std::map<int, defaultObject*>*>* dict, int light, glm::vec3 newcolor) {
	((Light*)(*(*dict)[LIGHT_TYPE])[light])->MAJlight(newcolor);
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

	std::map<int, std::map<int, defaultObject*>*> all;
	dictManager M(&all);

	M.add_element(new Shader("default.vert", "default.frag"), SHADER_TYPE);
	M.add_element(new Shader("light.vert", "light.frag"), SHADER_TYPE);

	M.add_element(new Texture("black16x16.png", GL_TEXTURE_2D, 1, GL_RGBA, GL_UNSIGNED_BYTE, nullptr), TEXTURE_TYPE);
	M.add_element(new Texture("planksSpec.png", GL_TEXTURE_2D, 1, GL_RED, GL_UNSIGNED_BYTE, nullptr), TEXTURE_TYPE);
	M.add_element(new Texture("brique.png", GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, M.getTexturePtr(0)), TEXTURE_TYPE);
	M.add_element(new Texture("cube_tex.png", GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, M.getTexturePtr(0)), TEXTURE_TYPE);
	M.add_element(new Texture("planks.png", GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, M.getTexturePtr(1)), TEXTURE_TYPE);

	//essayer de faire un seul shader qui gère les couleur et les texture

	//M.add_element(new Cube(1.0f, glm::vec3(-1.0f, 0.0f, 0.0f), M.getTexturePtr(1), M.getShaderPtr(0)), CUBE_TYPE);
	//M.add_element(new Cube(1.0f, glm::vec3(1.0f, 0.0f, 0.0f), M.getTexturePtr(1), M.getShaderPtr(0)), CUBE_TYPE);

	//M.getCubePtr(1)->Rotate(90.0f, glm::vec3(1.0f, 1.0f, 0.0f));
	M.add_element(new Plan(3.0f, glm::vec3(0.0f, -1.0f, 0.0f), M.getTexturePtr(4), M.getShaderPtr(0)), PLAN_TYPE);
	M.getPlanPtr(0)->Rotate(45, glm::vec3(1.0f, 0.0f, 0.0f));

	M.add_element(new Light(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f), 1.0f, glm::vec3(0.0f, -1.0f, 0.0f), 0.95f, 0.9f, all[SHADER_TYPE], 1), LIGHT_TYPE);
	
	MAJlightcolor(&all, 0);

	M.printingKeys();

	Camera camera = Camera(windowWidth, windowHeight, glm::vec3(0.0f, 0.0f, 5.0f), 45.0f, 0.1f, 20.0f, all[SHADER_TYPE]);
	camera.Matrix();

	//set ambient light in all shaders
	float ambientLight = 0.1f;
	std::map<int, defaultObject*>::iterator shaderIt;
	for (shaderIt = all[SHADER_TYPE]->begin(); shaderIt != all[SHADER_TYPE]->end(); shaderIt++) {
		Shader* crntShaderPtr = (Shader*)(shaderIt->second);
		crntShaderPtr->Activate();
		glUniform1f(glGetUniformLocation(crntShaderPtr->ID, "ambientLight"), ambientLight);
	}

	//set Background color
	float backgroundcolor[4] = { 0.07f, 0.13f, 0.17f, 1.0f };
	glClearColor(backgroundcolor[0], backgroundcolor[1], backgroundcolor[2], backgroundcolor[3]);
	glClear(GL_COLOR_BUFFER_BIT);

	// Swap the back buffer with the front buffer
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

		glClearColor(backgroundcolor[0], backgroundcolor[1], backgroundcolor[2], backgroundcolor[3]);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.Inputs(window);

		M.drawingElement(CUBE_TYPE, LIGHT_TYPE);

		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	};

	M.deleteAll();

	glfwTerminate();
	return 0;
}