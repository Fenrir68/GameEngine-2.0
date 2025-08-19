#include"Element.h"
#include"ToolBox.h"

Element::Element(Mesh mesh, glm::vec3 pos, glm::vec3 size, Shader* shader) {
	Element::mesh = mesh;
	Element::size = size;
	shaderProg = shader;
	Scale(size);
	Translate(pos);
}

void Element::addRotation(int ind, float value) {
	if (ind >= 0 && ind < 3) {
		rotation[ind] += value;
		if (rotation[ind] > 360.0f) {
			rotation[ind] -= 360.0f;
		}
		else if (rotation[ind] < 0.0f) {
			rotation[ind] += 360.0f;
		}
	}
	else {
		std::cout << "indice out of range : must be between 0 and 2 include\n";
	}
}

void Element::Draw() {
	mesh.Draw(*shaderProg, model);
}

void Element::Scale(glm::vec3 size) {
	model = glm::scale(model, size);
}

void Element::Translate(glm::vec3 depl) {
	position += depl;
	model = goTo(model, position);
}

void Element::Rotate(float angle, int axis_ind) {
	glm::vec3 axis = getAxis(axis_ind);
	if (axis != glm::vec3(0.0f)) {
		addRotation(axis_ind, angle);
		model = glm::rotate(model, glm::radians(angle), axis);
	}
}

void Element::Delete() {
	mesh.Delete();
}