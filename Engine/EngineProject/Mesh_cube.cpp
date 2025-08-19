#include"Mesh_cube.h"

Mesh_cube::Mesh_cube(std::vector<Texture> texVec) {
	Mesh::vertices = cube_vertVec;
	Mesh::indices = cube_indVec;
	Mesh::textures = texVec;

	Mesh_ctor();
}