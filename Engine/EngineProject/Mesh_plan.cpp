#include"Mesh_plan.h"

Mesh_plan::Mesh_plan(std::vector<Texture> texVec){
	Mesh::vertices = plan_vertVec;
	Mesh::indices = plan_indVec;
	Mesh::textures = texVec;

	Mesh::Mesh_ctor();
}