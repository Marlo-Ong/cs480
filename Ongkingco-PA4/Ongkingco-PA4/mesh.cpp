#include "mesh.h"

Mesh::Mesh()
{

}

Mesh::~Mesh()
{

}

bool Mesh::loadModelFromFile(const char* path) {
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate);

	if (!scene) {
		printf("couldn't open the .obj file.\n");
		return false;
	}
}


