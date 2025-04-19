#ifndef MESH_H
#define MESH_H

#include "graphics_headers.h"
#include "object.h"

class Mesh : public Object
{
  public:
    Mesh(const char* path);
    Mesh(const char* path, glm::vec3 pivot, float angle, float scale);
    ~Mesh();
    bool loadModelFromFile(const char* path);

    void Update(glm::mat4 model);
    void Render(GLint posAttrib, GLint colAttrib);

    glm::mat4 GetModel();

    bool InitBuffers();

private:
    glm::vec3 pivotLocation;
    glm::mat4 model;
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    GLuint VB;
    GLuint IB;

    GLuint vao;

    float angle;

    void setupModelMatrix(glm::vec3 pivotLoc, float angle, float scale);
};

#endif /* MESH_H */
