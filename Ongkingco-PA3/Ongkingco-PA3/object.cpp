#include "object.h"
#include <cstdlib> // for srand
#include <ctime>   // for time

// Destructor
Object::~Object()
{
	Vertices.clear();
	Indices.clear();
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

	// Seed the random function for different values on each run
	std::srand((unsigned int)(std::time(0)));

	// Generate a random orientation to rotate the object
	float rvec1 = glm::linearRand(-.1f, .1f) * 3.1415f;
	float rvec2 = glm::linearRand(-.1f, .1f) * 3.1415f;
	float rvec3 = glm::linearRand(-.2f, .2f) * 3.1415f;

	// Generate a random location to translate the object
	float tvec1 = glm::linearRand(-8.f, 8.f);
	float tvec2 = glm::linearRand(-8.f, 8.f);
	float tvec3 = glm::linearRand(-2.f, 2.f);

	// Apply translation transformation to the model matrix
	model = glm::translate(glm::mat4(1.0f), glm::vec3(tvec1, tvec2, tvec3));

	// Apply rotation transformation on each axis to the model matrix
	model = glm::rotate(model, rvec1, glm::vec3(1.0f, 0.0f, 0.0f)); // x rot
	model = glm::rotate(model, rvec2, glm::vec3(0.0f, 1.0f, 0.0f)); // y rot
	model = glm::rotate(model, rvec3, glm::vec3(0.0f, 0.0f, 1.0f)); // z rot

}

void Object::Update(unsigned int dt)
{
	model = glm::translate(model, m_speed);

	// EXTRA CREDIT (Ugrad section)
	// Rotate the model on its z-axis by its curent z-rotation speed.
	model = glm::rotate_slow(model, m_angSpeed.z, glm::vec3(0, 0, 1.f));
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
