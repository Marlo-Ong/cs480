#pragma once
#include "object.h"
class Sphere :
    public Object
{
public:
    Sphere();
    Sphere(glm::vec3 pivot);
    Sphere(glm::vec3 pivot, float angle);
    Sphere(glm::vec3 pivot, float angle, float scale);

    void Render(GLint positionAttribLoc, GLint colorAttribLoc);
    glm::mat4 GetModel() { return model; }
    void Update(glm::mat4 matModel);

private:
    glm::vec3 pivotLocation;
    glm::mat4 model;
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;

    static int instanceCount;
    int numVertices;
    int numIndices;
    int prec;

    GLuint VB;
    GLuint IB;

    GLuint vao;

    float angle;

    void setupVertices();
    void setupBuffers();
    void setupModelMatrix(glm::vec3 pivotLoc, float angle, float scale);
};

