#include "pyramid.h"

Pyramid::Pyramid()
{
    setupVertices();
    setupBuffers();
    setupModelMatrix(glm::vec3(0., 0., 0.), 0., 1.);
}

Pyramid::Pyramid(glm::vec3 pivot)
{
    setupVertices();
    setupBuffers();
    setupModelMatrix(pivot, glm::radians(0.0f), 1.f);
}

Pyramid::Pyramid(glm::vec3 pivot, float angle)
{
    setupVertices();
    setupBuffers();
    setupModelMatrix(pivot, glm::radians(angle), 1.f);
}

Pyramid::Pyramid(glm::vec3 pivot, float angle, float scale)
{
    setupVertices();
    setupBuffers();
    setupModelMatrix(pivot, glm::radians(angle), scale);
}


void Pyramid::Render(GLint positionAttribLoc, GLint colorAttribLoc)
{
    glBindVertexArray(vao);
    // Enable Vertext Attributes
    glEnableVertexAttribArray(positionAttribLoc);
    glEnableVertexAttribArray(colorAttribLoc);

    // Bind your VBO buffer(s) and then setup vertex attribute pointers
    glBindBuffer(GL_ARRAY_BUFFER, VB);
    glVertexAttribPointer(positionAttribLoc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
    glVertexAttribPointer(colorAttribLoc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));

    // Bind your index buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);

    // Render
    glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);

    // Disable Vertex Attribuates
    glDisableVertexAttribArray(positionAttribLoc);
    glDisableVertexAttribArray(colorAttribLoc);
}



void Pyramid::setupVertices() {
    Vertices = {
    {{.0f, 2.f, .0f},{1,1,1}}, // Top vertex
    {{1.0f, .0f, 1.0f},{0,1,0}},
    {{-1.0f, .0f, 1.0f},{0,0,1}}, 
    {{-1.0f, .0f, -1.0f},{1,0,0}},
    {{1.0f, .0f, -1.0f},{0,0,1}} // The four base vertices
    };

    Indices = {
      0, 1, 2,  // East face
      0, 2, 3,  // North face
      0, 3, 4,  // West face
      0, 4, 1,  // South face
      1, 2, 3,
      3, 4, 1 }; // The two bottom faces
}


void Pyramid::setupBuffers() {
    // For OpenGL 3
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &VB);
    glBindBuffer(GL_ARRAY_BUFFER, VB);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &IB);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * Indices.size(), &Indices[0], GL_STATIC_DRAW);
}

void Pyramid::setupModelMatrix(glm::vec3 pivot, float angle, float scale) {
    pivotLocation = pivot;
    model = glm::translate(glm::mat4(1.0f), pivotLocation);
    model *= glm::rotate(glm::mat4(1.f), angle, glm::vec3(0., 1., 0));
    model *= glm::scale(glm::vec3(scale, scale, scale));
}

void Pyramid::Update(glm::mat4 matModel) {
 
    model = matModel;

}