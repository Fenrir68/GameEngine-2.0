#include"Model.h"

Model::Model(const char* file) {

	Model::file = file;

	std::string text = get_file_contents(file);
	JSON = json::parse(text);

	data = getData();

	traverseNode(0);
}

void Model::Draw(Shader& shader) {
	for (unsigned int i = 0; i < meshes.size(); i++) {
		meshes[i].Draw(shader, matricesMeshes[i]);
	}
}

void Model::traverseNode(unsigned int nextNode, glm::mat4 previousMatrix) {

	json node = JSON["nodes"][nextNode];

	glm::vec3 translation = glm::vec3(0.0f);
	if (node.find("translation") != node.end()) {
		translation = glm::vec3(node["translation"][0], node["translation"][1], node["translation"][2]);
	}

	glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
	if (node.find("rotation") != node.end()) {
		rotation = glm::quat(node["rotation"][3], node["rotation"][0], node["rotation"][1], node["rotation"][2]);
	}

	glm::vec3 scale = glm::vec3(1.0f);
	if (node.find("scale") != node.end()) {
		scale = glm::vec3(node["scale"][0], node["scale"][1], node["scale"][2]);
	}

	glm::mat4 mat = glm::mat4(1.0f);
	if (node.find("matrix") != node.end()) {
		float matVal[16];
		for (int i = 0; i < 16; i++) {
			matVal[i] = node["matrix"][i];
		}
		mat = glm::make_mat4(matVal);
	}

	glm::mat4 trans = glm::translate(glm::mat4(1.0f), translation);
	glm::mat4 rot = glm::mat4_cast(rotation);
	glm::mat4 sca = glm::scale(glm::mat4(1.0f), scale);

	glm::mat4 currentMatrix = previousMatrix * mat * trans * rot * sca;

	if (node.find("mesh") != node.end()) {
		matricesMeshes.push_back(currentMatrix);
		PrintMat4(currentMatrix);
		loadMesh(node["mesh"]);
	}
	
	if (node.find("children") != node.end()) {
		for (unsigned int i = 0; i < node["children"].size(); i++) {
			traverseNode(node["children"][i], currentMatrix);
		}
	}

}

void Model::loadMesh(unsigned int meshInd) {

	unsigned int posAccInd = JSON["meshes"][meshInd]["primitives"][0]["attributes"]["POSITION"];
	unsigned int normalAccInd = JSON["meshes"][meshInd]["primitives"][0]["attributes"]["NORMAL"];
	unsigned int texAccInd = JSON["meshes"][meshInd]["primitives"][0]["attributes"]["TEXCOORD_0"];
	unsigned int indAccInd = JSON["meshes"][meshInd]["primitives"][0]["indices"];


	std::vector<glm::vec3> positions = groupFloatsVec3(getFloats(JSON["accessors"][posAccInd]));
	std::vector<glm::vec3> normals = groupFloatsVec3(getFloats(JSON["accessors"][normalAccInd]));
	std::vector<glm::vec2> texCoords = groupFloatsVec2(getFloats(JSON["accessors"][texAccInd]));
	std::vector<Vertex> vertices = assembleVertices(positions, normals, texCoords);


	std::vector<GLuint> indices = getIndices(JSON["accessors"][indAccInd]);
	std::vector<Texture> textures = getTextures();

	meshes.push_back(Mesh(vertices, indices, textures));
}

std::vector<unsigned char> Model::getData() {

	std::string bytesText;
	std::string uri = JSON["buffers"][0]["uri"];		//name of a .bin file which contains binary data

	std::string fileStr = std::string(file);
	std::string fileDriectory = fileStr.substr(0, fileStr.find_last_of('/') + 1);
	bytesText = get_file_contents((fileDriectory + uri).c_str());

	return std::vector<unsigned char>(bytesText.begin(), bytesText.end());
}

std::vector<float> Model::getFloats(json accessor) {

	std::vector<float> floatVec;

	unsigned int bufferViewInd = accessor.value("bufferView", 1);
	unsigned int count = accessor["count"];
	unsigned int accByteOffset = accessor.value("byteOffset", 0);
	std::string type = accessor["type"];

	json bufferView = JSON["bufferViews"][bufferViewInd];
	unsigned int byteOffset = bufferView["byteOffset"];

	unsigned int numPerVert;
	if (type == "SCALAR") numPerVert = 1;
	else if (type == "VEC2") numPerVert = 2;
	else if (type == "VEC3") numPerVert = 3;
	else if (type == "VEC4") numPerVert = 4;
	else throw std::invalid_argument("Type is invalid (SCALAR, VEC2, VEC3 or VEC4)");

	unsigned int beginningOfData = accByteOffset + byteOffset;
	unsigned int lenghtOfData = count * 4 * numPerVert;

	for (unsigned int i = beginningOfData; i < beginningOfData + lenghtOfData; i) {
		unsigned char bytes[] = { data[i++], data[i++], data[i++], data[i++] };		//4 bytes of a float
		float value;
		std::memcpy(&value, bytes, 4);		//transform char into float
		floatVec.push_back(value);
	}

	return floatVec;

}

std::vector<GLuint> Model::getIndices(json accessor) {

	std::vector<GLuint> indVec;

	unsigned int bufferViewInd = accessor.value("bufferView", 1);
	unsigned int count = accessor["count"];
	unsigned int accByteOffset = accessor.value("byteOffset", 0);
	unsigned int compType = accessor["componentType"];

	json bufferView = JSON["bufferViews"][bufferViewInd];
	unsigned int byteOffset = bufferView["byteOffset"];

	unsigned int beginningOfData = accByteOffset + byteOffset;
	if (compType == 5125) {			//unsigned int
		for (unsigned int i = beginningOfData; i < beginningOfData + count * 4; i) {
			unsigned char bytes[] = { data[i++], data[i++], data[i++], data[i++] };		//4 bytes of a float
			unsigned int value;
			std::memcpy(&value, bytes, 4);
			indVec.push_back((GLuint)value);
		}
	}
	else if (compType == 5123) {	//unsigned short
		for (unsigned int i = beginningOfData; i < beginningOfData + count * 2; i) {
			unsigned char bytes[] = { data[i++], data[i++] };		//4 bytes of a float
			unsigned short value;
			std::memcpy(&value, bytes, 2);
			indVec.push_back((GLuint)value);
		}
	}
	else if (compType == 5122) {	//short
		for (unsigned int i = beginningOfData; i < beginningOfData + count * 2; i) {
			unsigned char bytes[] = { data[i++], data[i++] };		//4 bytes of a float
			short value;
			std::memcpy(&value, bytes, 2);
			indVec.push_back((GLuint)value);
		}
	}

	return indVec;
}

std::vector<Texture> Model::getTextures() {

	std::vector<Texture> textures;

	std::string fileStr = std::string(file);
	std::string fileDirectory = fileStr.substr(0, fileStr.find_last_of('/') + 1);

	for (unsigned int i = 0; i < JSON["images"].size(); i++) {

		std::string texBin = JSON["images"][i]["uri"];		//name of binary data file

		bool skip = false;
		for (unsigned int k = 0; k < loadedTexName.size(); k++) {
			if (texBin == loadedTexName[k]) {
				skip = true;
				textures.push_back(loadedTex[k]);
				break;
			}
		}

		if (!skip) {
			const char* texType = "NONE";
			if (texBin.find("baseColor") != std::string::npos) {
				texType = "diffuse";
			}
			else if (texBin.find("metallicRoughness") != std::string::npos) {
				texType = "specular";
			}
			if (texType != "NONE") {
				Texture tex = Texture((fileDirectory + texBin).c_str(), texType, loadedTex.size());
				textures.push_back(tex);
				loadedTex.push_back(tex);
				loadedTexName.push_back(texBin);
			}
			//else throw std::invalid_argument("Unknown texture type");
		}
	}
	return textures;
}

std::vector<Vertex> Model::assembleVertices(
	std::vector<glm::vec3> position,
	std::vector<glm::vec3> normal,
	std::vector<glm::vec2> tex
) {
	std::vector<Vertex> vertices;
	for (unsigned int i = 0; i < position.size(); i++) {
		vertices.push_back(
			Vertex{
				position[i],
				normal[i],
				hexaDecode("600"),
				tex[i]
			}
		);
	}
	return vertices;
}

std::vector<glm::vec2> Model::groupFloatsVec2(std::vector<float> floatVec) {
	std::vector<glm::vec2> vectors;

	for (unsigned int i = 0; i < floatVec.size(); i) {
		vectors.push_back(glm::vec2(floatVec[i++], floatVec[i++]));
	}
	return vectors;
}

std::vector<glm::vec3> Model::groupFloatsVec3(std::vector<float> floatVec) {
	std::vector<glm::vec3> vectors;

	for (unsigned int i = 0; i < floatVec.size(); i) {
		vectors.push_back(glm::vec3(floatVec[i++], floatVec[i++], floatVec[i++]));
	}
	return vectors;
}

std::vector<glm::vec4> Model::groupFloatsVec4(std::vector<float> floatVec) {
	std::vector<glm::vec4> vectors;

	for (unsigned int i = 0; i < floatVec.size(); i) {
		vectors.push_back(glm::vec4(floatVec[i++], floatVec[i++], floatVec[i++], floatVec[i++]));
	}
	return vectors;
}

void Model::Delete() {
	for (unsigned int i = 0; i < meshes.size(); i++) {
		meshes[i].Delete();
	}
	for (unsigned int j = 0; j < loadedTex.size(); j++) {
		loadedTex[j].Delete();
	}
}