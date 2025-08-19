#include"ToolBox.h"

glm::vec3 hexaDecode(std::string chaine) {
	glm::vec3 decode(0.0f);
	if (chaine.size() == 3) {
		std::map<char, float> hexaMap = { {'0',0.0f}, {'1',1.0f}, {'2',2.0f}, {'3',3.0f}, {'4',4.0f}, {'5',5.0f}, {'6',6.0f}, {'7',7.0f},
									  {'8',8.0f}, {'9',9.0f}, {'A',10.0f}, {'B',11.0f}, {'C',12.0f}, {'D',13.0f}, {'E',14.0f}, {'F',15.0f} };

		for (int i = 0; i < 3; i++) {
			decode[i] = hexaMap[chaine[i]] / 15.0f;
		}
	}
	return decode;
}

void PrintMat4(glm::mat4 matrix) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			std::cout << matrix[j][i] << "    ";
		}
		std::cout << std::endl;
	}
}

glm::mat4 goTo(glm::mat4 matrix, glm::vec3 coordinate) {
	for (int k = 0; k < 3; k++) {
		matrix[3][k] = coordinate[k];
	}
	return matrix;
}

glm::mat4 scale(glm::mat4 matrix, glm::vec3 scaling) {
	for (int i = 0; i < 3; i++) {
		matrix[i][i] = scaling[i];
	}
	return matrix;
}

glm::vec3 getAxis(int axis_ind) {
	glm::vec3 axis(0.0f);
	if (0 <= axis_ind && axis_ind < 3) {
		axis[axis_ind] = 1.0f;
	}
	else {
		std::cout << "Axis indice out of range : must be between 0 and 2 include\n";
	}
	return axis;
}