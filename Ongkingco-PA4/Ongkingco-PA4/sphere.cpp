#include "sphere.h"

int Sphere::instanceCount = 0;

Sphere::Sphere()
{
    setupVertices();
    setupBuffers();
    setupModelMatrix(glm::vec3(0., 0., 0.), 0., 1.);
}

Sphere::Sphere(glm::vec3 pivot)
{
    setupVertices();
    setupBuffers();
    setupModelMatrix(pivot, glm::radians(0.0f), 1.f);
}

Sphere::Sphere(glm::vec3 pivot, float angle)
{
    setupVertices();
    setupBuffers();
    setupModelMatrix(pivot, glm::radians(angle), 1.f);
}

Sphere::Sphere(glm::vec3 pivot, float angle, float scale)
{
    setupVertices();
    setupBuffers();
    setupModelMatrix(pivot, glm::radians(angle), scale);
}


void Sphere::Render(GLint positionAttribLoc, GLint colorAttribLoc)
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



void Sphere::setupVertices() {
    prec = 10;
    numVertices = (prec + 1) * (prec + 1);
    numIndices = prec * prec * 6;
    instanceCount++;

    for (int i = 0; i < numVertices; i++) { Vertices.push_back(Vertex(glm::vec3(0, 0, 0), (glm::vec3(0, 0, 0)))); }
    for (int i = 0; i < numIndices; i++) { Indices.push_back(0); }

    // calculate triangles vertices
    for (int i = 0; i <= prec; i++) {
        for (int j = 0; j <= prec; j++) {
            float y = (float)cos(glm::radians(180.f - i * 180.f / prec));
            float x = -(float)cos(glm::radians(j * 360.f / prec)) * (float)abs(cos(asin(y)));
            float z = (float)sin(glm::radians(j * 360.f / prec)) * (float)abs(cos(asin(y)));

            // Distinguish different color for every 2nd sphere created
            glm::vec3 bodyColor = (instanceCount % 2)
                ? glm::vec3(x, y, z) // RGB
                : glm::vec3(1.0f) - glm::vec3(x, y, z); // CMY

            Vertices[(i * (prec + 1) + j)] = Vertex(glm::vec3(x, y, z), bodyColor);
        }
    }

    // calculate triangles indices
    for (int i = 0; i < prec; i++) { // for each horizontal slice
        for (int j = 0; j < prec; j++) { // for each vertex in slice

            // set indices for triangle 1
            Indices[6 * (i * prec + j) + 0] = i * (prec + 1) + j; // current vertex (bottom-left)
            Indices[6 * (i * prec + j) + 1] = i * (prec + 1) + j + 1; // right vertex
            Indices[6 * (i * prec + j) + 2] = (i + 1) * (prec + 1) + j; // above vertex

            // set indices for traingle 2
            Indices[6 * (i * prec + j) + 3] = i * (prec + 1) + j + 1; // right vertex
            Indices[6 * (i * prec + j) + 4] = (i + 1) * (prec + 1) + j + 1; // above-right vertex
            Indices[6 * (i * prec + j) + 5] = (i + 1) * (prec + 1) + j; // above vertex
        }
    }
}


void Sphere::setupBuffers() {
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

void Sphere::setupModelMatrix(glm::vec3 pivot, float angle, float scale) {
    pivotLocation = pivot;
    model = glm::translate(glm::mat4(1.0f), pivotLocation);
    model *= glm::rotate(glm::mat4(1.f), angle, glm::vec3(0., 1., 0));
    model *= glm::scale(glm::vec3(scale, scale, scale));
}

void Sphere::Update(glm::mat4 matModel) {
 
    model = matModel;
}