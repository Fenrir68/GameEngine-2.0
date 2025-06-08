#include "Camera.h"

Camera::Camera(int width, int height, glm::vec3 position, Shader* shader) {
	Camera::windowWidth = width;
	Camera::windowHeight = height;
	shaderPtr = shader;
	Position = position;
}

void Camera::Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform) {

	view = glm::lookAt(Position, Position + Orientation, Up);
	proj = glm::perspective(glm::radians(FOVdeg), (float)(windowWidth) / windowHeight, nearPlane, farPlane);
	BindMatCam();
}

void Camera::MAJviewMat() {
	view = glm::lookAt(Position, Position + Orientation, Up);
	BindMatCam();
}

void Camera::BindMatCam() {
	(*shaderPtr).Activate();
	glUniformMatrix4fv(glGetUniformLocation((*shaderPtr).ID, "mat4Cam"), 1, GL_FALSE, glm::value_ptr(proj * view));
}

void Camera::Inputs(GLFWwindow* window) {

	//glm::cross = produit vectoriel
	//GLFW_KEY fonctionne en QWERTY pas en AZERTY
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		Position += 0.5f * speed * Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		Position += 0.5f * speed * -Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		Position += 0.5f * speed * glm::normalize(glm::cross(Orientation, Up));
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		Position += 0.5f * speed * -glm::normalize(glm::cross(Orientation, Up));
	}
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
		if (firstClick) {
			//(0,0) top left		//(windowWidth, windowHeight) bottom right
			glfwGetCursorPos(window, &mouseX, &mouseY);
			firstClick = false;
		}
		else {
			double newMouseX, newMouseY;
			glfwGetCursorPos(window, &newMouseX, &newMouseY);
			float rotY = (newMouseX-mouseX) / windowWidth;
			float rotX = (newMouseY-mouseY) / windowHeight;
			Orientation = glm::rotate(Orientation, rotY * sensitivity, Up);
			Orientation = glm::rotate(Orientation, rotX * sensitivity, glm::cross(Orientation, Up));
			mouseX = newMouseX;
			mouseY = newMouseY;
		}
	}
	else {
		firstClick = true;
	}
	MAJviewMat();
}
