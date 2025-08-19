#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include"glm/gtc/matrix_transform.hpp"
#include"glm/gtc/type_ptr.hpp"

#include"Model.h"
#include"Mesh_plan.h"
#include"Mesh_cube.h"
#include"Light.h"

//Reprendre la video sur les model à 8:22

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

	std::map<int, Shader*> shader_map;
	shader_map[0] = new Shader("default.vert", "default.frag");
	shader_map[1] = new Shader("light.vert", "light.frag");

	Texture planksTex[] = {
		Texture("planks.png", "diffuse", 0),
		Texture("planksSpec.png", "specular", 1)
	};
	std::vector<Texture> planksTexVec(planksTex, planksTex + 2);

	Mesh_plan floor_mesh(planksTexVec);

	Texture cubeTex[] = {
		Texture("cube_tex.png", "diffuse", 0),
		Texture("white16x16.png", "specular", 1)
	};
	std::vector<Texture> cubeTexVec(cubeTex, cubeTex + 2);

	Mesh_cube cube_mesh(cubeTexVec);

	Element floor(floor_mesh, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(2.0f), shader_map[0]);

	Element cube(cube_mesh, glm::vec3(2.0f, 0.0f, 0.0f), glm::vec3(1.0f), shader_map[0]);

	Light light(cube_mesh, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.1f), hexaDecode("FFF"), 4.0f, &shader_map, 1);

	light.MAJlight(glm::vec3(0.0f, -1.0f, 0.0f), 0.99f, 0.95f);

	Camera camera = Camera(windowWidth, windowHeight, glm::vec3(0.0f, 0.0f, 5.0f), 45.0f, 0.1f, 100.0f, &shader_map);
	camera.Matrix();

	//BORDEL START --------------------------------------------------------------------------------------------------
	

	Model sword = Model("model/sword/scene.gltf");


	//BODREL END ----------------------------------------------------------------------------------------------------

	//set ambient light in all shaders
	float ambientLight = 0.1f;
	std::map<int, Shader*>::iterator shaderIt;
	for (shaderIt = shader_map.begin(); shaderIt != shader_map.end(); shaderIt++) {
		Shader* crntShaderPtr = (Shader*)(shaderIt->second);
		crntShaderPtr->Activate();
		glUniform1f(glGetUniformLocation(crntShaderPtr->ID, "ambientLight"), ambientLight);
	}

	//set Background color
	glm::vec3 backgroundcolor = hexaDecode("033");
	glClearColor(backgroundcolor[0], backgroundcolor[1], backgroundcolor[2], 1.0f);
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

		glClearColor(backgroundcolor[0], backgroundcolor[1], backgroundcolor[2], 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.Inputs(window);

		sword.Draw(*shader_map[0]);
		//light.Draw();
		cube.Draw();
		//floor.Draw();

		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	};

	for (shaderIt = shader_map.begin(); shaderIt != shader_map.end(); shaderIt++) {
		Shader* crntShaderPtr = (Shader*)(shaderIt->second);
		crntShaderPtr->Delete();
		glUniform1f(glGetUniformLocation(crntShaderPtr->ID, "ambientLight"), ambientLight);
	}
	light.Delete();
	floor.Delete();
	sword.Delete();
	cube.Delete();
	
	glfwTerminate();
	return 0;
}