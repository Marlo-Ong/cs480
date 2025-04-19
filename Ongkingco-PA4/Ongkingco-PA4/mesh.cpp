#include "mesh.h"

Mesh::Mesh(const char* path)
{
    loadModelFromFile(path);

    // Model Set Up
    angle = 0.0f;
    pivotLocation = glm::vec3(0.f, 0.f, 0.f);
    model = glm::translate(glm::mat4(1.0f), pivotLocation);

    // Buffer Set Up
    if (!InitBuffers()) {
        printf("Some buffers not initialized.\n");
    }
}

Mesh::Mesh(const char* path, glm::vec3 pivot, float angle, float scale)
{
	loadModelFromFile(path);

	// Model Set Up
	setupModelMatrix(pivot, scale, angle);

		// Buffer Set Up
	if (!InitBuffers()) {
		printf("Some buffers not initialized.\n");
	}
}

Mesh::~Mesh()
{
	Vertices.clear();
	Indices.clear();
}

bool Mesh::loadModelFromFile(const char* path) {
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate);

	if (!scene) {
		printf("couldn't open the .obj file.\n");
		return false;
	}
	
    const int invertTotalSize = 2 * sizeof(aiVector3D);

    int iTotalVerts = 0;

    for (int i = 0; i < scene->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[i];
        int iMeshFaces = mesh->mNumFaces;
        for (int j = 0; j < iMeshFaces; j++) {
            const aiFace& face = mesh->mFaces[j];
            for (int k = 0; k < 3; k++) {
				aiVector3D v = mesh->mVertices[face.mIndices[k]];
                Vertices.push_back(Vertex(
                    glm::vec3(v.x, v.y, v.z),
					glm::vec3(v.x, v.y, v.z)));
            }
        }
        iTotalVerts += mesh->mNumVertices;
    }

    for (int i = 0; i < Vertices.size(); i++) {
        Indices.push_back(i);
    }

    return true;

}

void Mesh::Update(glm::mat4 inmodel)
{
	model = inmodel;

}

glm::mat4 Mesh::GetModel()
{
	return model;
}

void Mesh::Render(GLint posAttribLoc, GLint colAttribLoc)
{

	glBindVertexArray(vao);

	// Enable vertex attibute arrays for each vertex attrib
	glEnableVertexAttribArray(posAttribLoc);
	glEnableVertexAttribArray(colAttribLoc);

	// Bind your VBO
	glBindBuffer(GL_ARRAY_BUFFER, VB);

	// Set vertex attribute pointers to the load correct data
	glVertexAttribPointer(posAttribLoc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(colAttribLoc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));

	// Bind your Element Array
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);

	// Render
	glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);

	// Disable vertex arrays
	glDisableVertexAttribArray(posAttribLoc);
	glDisableVertexAttribArray(colAttribLoc);
}


bool Mesh::InitBuffers() {

	// For OpenGL 3
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &VB);
	glBindBuffer(GL_ARRAY_BUFFER, VB);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &IB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * Indices.size(), &Indices[0], GL_STATIC_DRAW);

	return true;
}

void Mesh::setupModelMatrix(glm::vec3 pivot, float angle, float scale) {
	pivotLocation = pivot;
	model = glm::translate(glm::mat4(1.0f), pivotLocation);
	model *= glm::rotate(glm::mat4(1.f), angle, glm::vec3(0., 1., 0));
	model *= glm::scale(glm::vec3(scale, scale, scale));
}


