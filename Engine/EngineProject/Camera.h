#pragma once
#include <map>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include "glm/gtx/vector_angle.hpp"

#include "shaderClass.h"

class Camera {
public:
	glm::vec3 Position;
	float speed = 0.1f;

	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	float sensitivity = 1.0f;

	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

	float FOV;
	float zsens = 5.0f;

	int windowWidth, windowHeight;
	float ratioW_H;

	float nearPlane, farPlane;

	glm::mat4 proj = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f); 
	std::map<int, Shader*>* shadersPtr;

	bool firstClick = true;
	double mouseX, mouseY;
	float angle_limit = 5.0f;

	Camera(int width, int height, glm::vec3 position, float baseFOV, float nearplane, float farplane, std::map<int, Shader*>* shaders_ptr);

	void Matrix();
	void BindMatCam();
	void Inputs(GLFWwindow* window);
};