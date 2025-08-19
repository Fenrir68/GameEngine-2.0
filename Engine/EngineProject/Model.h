#pragma once
#include<json/json.h>
#include"Mesh.h"
#include"ToolBox.h"

using json = nlohmann::json;

class Model {
public:
	Model(const char* file);

	void Draw(Shader& shader);

	void Delete();

private:
	const char* file;
	std::vector<unsigned char> data;

	std::vector<Mesh>meshes;
	std::vector<glm::mat4>matricesMeshes;

	std::vector<std::string> loadedTexName;
	std::vector<Texture> loadedTex;

	void traverseNode(unsigned int nextNode, glm::mat4 mat = glm::mat4(1.0f));

	void loadMesh(unsigned int meshInd);

	std::vector<unsigned char> getData();		//extract binary data from json file
	std::vector<float> getFloats(json accesor);
	std::vector<GLuint> getIndices(json accesor);
	std::vector<Texture> getTextures();

	std::vector<Vertex> assembleVertices(
		std::vector<glm::vec3> position,
		std::vector<glm::vec3> normal,
		std::vector<glm::vec2> tex
	);

	std::vector<glm::vec2> groupFloatsVec2(std::vector<float> floatVec);
	std::vector<glm::vec3> groupFloatsVec3(std::vector<float> floatVec);
	std::vector<glm::vec4> groupFloatsVec4(std::vector<float> floatVec);

	json JSON;
};