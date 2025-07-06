#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"glm/gtc/type_ptr.hpp"

class defaultObject {
public:
	virtual void Delete();
};

class drawableObject: public defaultObject {

	public:
		glm::vec3 Position;

		glm::mat4 model = glm::mat4(1.0f);
		void Translate(glm::vec3 vector);
		void goTo(glm::vec3 newPos);
		void Rotate(float angle, glm::vec3 axe);
		virtual void Draw();
};