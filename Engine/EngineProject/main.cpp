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
#include"light.h"
#include"defaultObject.h"

#define SHADER_CODE 0
#define TEXTURE_CODE 1
#define CUBE_CODE 2
#define LIGHT_CODE 3

void add_element(std::map<int, std::map<int, defaultObject*>*>* dict, defaultObject* element, int type) {
	if (!dict->count(type)) {
		(*dict)[type] = new std::map<int, defaultObject*>;
	}
	int n = (*dict)[type]->size();
	(*(*dict)[type])[n] = element;
}

void printingKeys(std::map<int, std::map<int, defaultObject*>*>* dict) {
	std::map<int, std::map<int, defaultObject*>*>::iterator it;
	for (it = dict->begin(); it != dict->end(); it++) {
		std::cout << "-------" << it->first << std::endl;

		std::map<int, defaultObject*>* crnt_map_ptr = (it->second);
		std::map<int, defaultObject*>::iterator it1;
		for (it1 = crnt_map_ptr->begin(); it1 != crnt_map_ptr->end(); it1++) {
			std::cout << it1->first << std::endl;
		}
	}
}

void drawingElement(std::map<int, std::map<int, defaultObject*>*>* dict, int beginCODE, int endCODE) {
	for (int k = beginCODE; k <= endCODE; k++) {
		if (dict->count(k)) {
			std::map<int, defaultObject*>* crnt_map = (*dict)[k];
			std::map<int, defaultObject*>::iterator ite = crnt_map->begin();
			for (ite; ite != crnt_map->end(); ite++) {
				((drawableObject*)ite->second)->Draw();
			}
		}
	}
}

void MAJlightcolor(std::map<int, std::map<int, defaultObject*>*>* dict, int light) {
	((Light*)(*(*dict)[LIGHT_CODE])[light])->MAJcolor();
}

void MAJlightcolor(std::map<int, std::map<int, defaultObject*>*>* dict, int light, glm::vec3 newcolor) {
	((Light*)(*(*dict)[LIGHT_CODE])[light])->MAJcolor(newcolor);
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

	std::map<int, std::map<int, defaultObject*>*> all; //000->099 = shader // 100->199 = textures // 200->299 = cube

	add_element(&all, new Shader("texture.vert", "texture.frag"), SHADER_CODE);
	add_element(&all, new Shader("color.vert", "color.frag"), SHADER_CODE);
	add_element(&all, new Shader("light.vert", "light.frag"), SHADER_CODE);

	add_element(&all, new Texture("brique.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE), TEXTURE_CODE);
	add_element(&all, new Texture("cube_tex.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE), TEXTURE_CODE);

	add_element(&all, new cube(1.0f, glm::vec3(-1.0f, 0.0f, 0.0f), (Texture*)(*(all[TEXTURE_CODE]))[1], (Shader*)((*(all[SHADER_CODE]))[0])), CUBE_CODE);
	add_element(&all, new cube(1.0f, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f), (Shader*)((*(all[SHADER_CODE]))[1])), CUBE_CODE);

	add_element(&all, new Light(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(2.0f, 2.0f, 2.0f), 0.5f, all[SHADER_CODE], 2), LIGHT_CODE);
	
	MAJlightcolor(&all, 0);

	printingKeys(&all);

	Camera camera = Camera(windowWidth, windowHeight, glm::vec3(0.0f, 0.0f, 2.5f), 45.0f, 0.1f, 20.0f, all[SHADER_CODE]);
	camera.Matrix();

	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
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

		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.Inputs(window);

		drawingElement(&all, CUBE_CODE, LIGHT_CODE);
		
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	};

	std::map<int, std::map<int, defaultObject*>*>::iterator it;
	for (it = all.begin(); it != all.end(); it++) {
		std::map<int, defaultObject*>* crnt_map_ptr = (it->second);
		std::map<int, defaultObject*>::iterator it1;
		for (it1 = crnt_map_ptr->begin(); it1 != crnt_map_ptr->end(); it1++) {
			it1->second->Delete();
		}
		crnt_map_ptr->clear();
	}
	all.clear();

	glfwTerminate();
	return 0;
}