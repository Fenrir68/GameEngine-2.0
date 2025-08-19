#pragma once
#include <iostream>
#include <map>
#include"glm/glm.hpp"

glm::vec3 hexaDecode(std::string chaine);

void PrintMat4(glm::mat4 matrix);

glm::mat4 goTo(glm::mat4 matrix, glm::vec3 coordinate);

glm::mat4 scale(glm::mat4 matrix, glm::vec3 scaling);

glm::vec3 getAxis(int axis_ind);