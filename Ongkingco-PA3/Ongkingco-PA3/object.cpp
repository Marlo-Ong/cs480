#include "object.h"
#include <cstdlib> // for srand
#include <ctime>   // for time

// Destructor
Object::~Object()
{
	Vertices.clear();
	Indices.clear();
}

void Object::setupModelMatrix(glm::vec3 pivot, float angle, float scale)
{
	pivotLocation = pivot;
	model = glm::translate(glm::mat4(1.0f), pivotLocation);
	model *= glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0., 1., 0.));
	model *= glm::scale(glm::vec3(scale, scale, scale));
}

glm::mat4 Object::GetModel()
{
	return model;
}

void Object::Initialize(GLint posAttribLoc, GLint colAttribLoc) {

	// Set up vertex array object
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Set up vertex buffer object
	glGenBuffers(1, &VB);
	glBindBuffer(GL_ARRAY_BUFFER, VB);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(posAttribLoc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(colAttribLoc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));

	// Set the index of the vertex buffer object
	glGenBuffers(1, &IB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * Indices.size(), &Indices[0], GL_STATIC_DRAW);
}

void Object::Update(glm::mat4 newModel)
{
	model = newModel;
}

void Object::Render(GLint posAttribLoc, GLint colAttribLoc)
{
	// Bind vertex array object
	glBindVertexArray(vao);

	// Bind vertex buffer object(s)
	glBindBuffer(GL_ARRAY_BUFFER, VB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);

	// enable the vertex attribute arrays 
	// this is the poistion attrib in the vertex shader
	glEnableVertexAttribArray(posAttribLoc);
	// this is the color attribe in the vertex shader
	glEnableVertexAttribArray(colAttribLoc);

	// Draw call to OpenGL
	glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);

	// disable the vertex attributes
	glDisableVertexAttribArray(posAttribLoc);
	glDisableVertexAttribArray(colAttribLoc);

	// unbind VBO(s) and ElementBuffer(s)
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
