#include"defaultObject.h"
#include<iostream>
void defaultObject::Delete() {
	std::cout << "defaultObject version" << std::endl;
}

void drawableObject::Draw() {
	std::cout << "drawableObject version" << std::endl;
}