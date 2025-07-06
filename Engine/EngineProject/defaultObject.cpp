#include"defaultObject.h"
#include<iostream>
void defaultObject::Delete() {
	std::cout << "defaultObject DELETE version" << std::endl;
}

void drawableObject::Draw() {
	std::cout << "drawableObject DRAW version" << std::endl;
}

void drawableObject::Rotate(float angle, glm::vec3 axe) {
	model = glm::rotate(model, glm::radians(angle), axe);
}

void drawableObject::Translate(glm::vec3 vector) {
	model = glm::translate(model, vector);
	Position += vector;
}

void drawableObject::goTo(glm::vec3 newPos) {
	model = glm::mat4(1.0f);
	Position = newPos;
	Translate(newPos);
}