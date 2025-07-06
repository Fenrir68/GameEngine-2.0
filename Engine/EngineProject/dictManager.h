#pragma once
#include <iostream>
#include <map>
#include "defaultObject.h"
#include "shaderClass.h"
#include "textureClass.h"
#include "cube.h"
#include "Plan.h"
#include "light.h"

#define SHADER_TYPE 0
#define TEXTURE_TYPE 1
#define CUBE_TYPE 2
#define PLAN_TYPE 3
#define LIGHT_TYPE 4
#define allTYPE {SHADER_TYPE, TEXTURE_TYPE, CUBE_TYPE, PLAN_TYPE, LIGHT_TYPE}

class dictManager {
public:
	std::map<int, std::map<int, defaultObject*>*>* dict;

	dictManager(std::map<int, std::map<int, defaultObject*>*>* dict);

	void add_element(defaultObject* element, int type);
	void printingKeys();
	defaultObject* getElementPtr(int type, int ind);
	Shader* getShaderPtr(int ind);
	Texture* getTexturePtr(int ind);
	Cube* getCubePtr(int ind);
	Plan* getPlanPtr(int ind);
	Light* getLightPtr(int ind);
	void deleteAll();
	void drawingElement(int beginCODE, int endCODE);
};
