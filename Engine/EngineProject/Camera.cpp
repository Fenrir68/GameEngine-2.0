#include "Camera.h"

Camera::Camera(int width, int height, glm::vec3 position, float baseFOV, float nearplane, float farplane, std::map<int, defaultObject*>* shaders_ptr) {
	Camera::windowWidth = width;
	Camera::windowHeight = height;
	ratioW_H = (float)(windowWidth) / windowHeight;
	FOV = baseFOV;
	nearPlane = nearplane;
	farPlane = farplane;
	Position = position;
	shadersPtr = shaders_ptr;
	
}

void Camera::Matrix() {
	view = glm::lookAt(Position, Position + Orientation, Up);
	proj = glm::perspective(glm::radians(FOV), ratioW_H, nearPlane, farPlane);
	BindMatCam();
}

void Camera::BindMatCam() {
	std::map<int, defaultObject*>::iterator it;
	for (it = shadersPtr->begin(); it!=shadersPtr->end(); it++) {
		Shader* crnt_shader_ptr = ((Shader*)(it->second));
		crnt_shader_ptr->Activate();
		glUniformMatrix4fv(glGetUniformLocation(crnt_shader_ptr->ID, "mat4Cam"), 1, GL_FALSE, glm::value_ptr(proj * view));
	}
}

void Camera::Inputs(GLFWwindow* window) {
	//glm::cross = produit vectoriel
	//GLFW_KEY fonctionne en QWERTY pas en AZERTY
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && FOV > zsens) {
			FOV -= zsens;
		}
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS && FOV < 90.0f - zsens) {
			FOV += zsens;
		}
		if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
			FOV = 45.0f;
		}
	}
	else {
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			Position += speed * Orientation;
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			Position += speed * -Orientation;
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			Position += speed * glm::normalize(glm::cross(Orientation, Up));
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			Position += speed * -glm::normalize(glm::cross(Orientation, Up));
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
			Position += speed * -Up;
		}
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
			Position += speed * Up;
		}
		//reset orientation
		if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
			Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
		}
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			if (firstClick) {
				//(0,0) top left		//(windowWidth, windowHeight) bottom right
				glfwGetCursorPos(window, &mouseX, &mouseY);
				firstClick = false;
			}
			else {
				double newMouseX, newMouseY;
				glfwGetCursorPos(window, &newMouseX, &newMouseY);
				float rotY = (newMouseX - mouseX) / windowWidth;
				float rotX = (newMouseY - mouseY) / windowHeight;
				Orientation = glm::rotate(Orientation, rotY * sensitivity, Up);
				float angle = glm::angle(Orientation, Up);
				//prevent backflip and frontflip
				if ((rotX > 0 && angle >= glm::radians(angle_limit)) ||
					(rotX < 0 && angle <= glm::radians(180 - angle_limit))) {
					Orientation = glm::rotate(Orientation, rotX * sensitivity, glm::cross(Orientation, Up));
				}
				mouseX = newMouseX;
				mouseY = newMouseY;
			}
		}
		else {
			firstClick = true;
		}
	}
	Matrix();
}



