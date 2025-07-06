#include "dictManager.h"

dictManager::dictManager(std::map<int, std::map<int, defaultObject*>*>* dict) {
	dictManager::dict = dict;
}

void dictManager::add_element(defaultObject* element, int type) {
	if (!dict->count(type)) {
		(*dict)[type] = new std::map<int, defaultObject*>;
	}
	int n = (*dict)[type]->size();
	(*(*dict)[type])[n] = element;
}

void dictManager::printingKeys() {
	std::cout << "start PRINTING KEYS" << std::endl;
	std::map<int, std::map<int, defaultObject*>*>::iterator it;
	for (it = dict->begin(); it != dict->end(); it++) {
		std::cout << "-------" << it->first << std::endl;

		std::map<int, defaultObject*>* crnt_map_ptr = (it->second);
		std::map<int, defaultObject*>::iterator it1;
		for (it1 = crnt_map_ptr->begin(); it1 != crnt_map_ptr->end(); it1++) {
			std::cout << it1->first << std::endl;
		}
	}
	std::cout << "end PRINTING KEYS////////////////" << std::endl;
}

defaultObject* dictManager::getElementPtr(int type, int ind) {
	return (*((*dict)[type]))[ind];
}

Shader* dictManager::getShaderPtr(int ind) {
	return (Shader*)getElementPtr(SHADER_TYPE, ind);
}

Texture* dictManager::getTexturePtr(int ind) {
	return (Texture*)getElementPtr(TEXTURE_TYPE, ind);
}

Cube* dictManager::getCubePtr(int ind) {
	return (Cube*)getElementPtr(CUBE_TYPE, ind);
}

Plan* dictManager::getPlanPtr(int ind) {
	return (Plan*)getElementPtr(PLAN_TYPE, ind);
}

Light* dictManager::getLightPtr(int ind) {
	return (Light*)getElementPtr(LIGHT_TYPE, ind);
}

void dictManager::deleteAll() {
	std::cout << "start DELETING" << std::endl;
	for (int type : allTYPE) {
		std::map<int, defaultObject*>* crnt_map_ptr = (*dict)[type];
		if (crnt_map_ptr != nullptr) {
			int n = crnt_map_ptr->size();
			std::cout << "-----------" << type << std::endl;
			for (int k = 0; k < n; k++) {
				std::cout << k << std::endl;
				(*crnt_map_ptr)[k]->Delete();
			}crnt_map_ptr->clear();
		}
	}dict->clear();
	std::cout << "end DELETING///////////////////" << std::endl;
}

void dictManager::drawingElement(int beginCODE, int endCODE) {
	for (int k = beginCODE; k <= endCODE; k++) {
		if (dict->count(k)) {
			std::map<int, defaultObject*>* crnt_map = (*dict)[k];
			std::map<int, defaultObject*>::iterator ite = crnt_map->begin();
			for (ite; ite != crnt_map->end(); ite++) {
				((drawableObject*)ite->second)->Draw();
			}
		}
	}
}