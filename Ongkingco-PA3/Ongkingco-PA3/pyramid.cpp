#include "pyramid.h"

Pyramid::Pyramid() {
	createVertices();
}

void Pyramid::createVertices() {

	// Define vertices and colors for pyramid
	Vertices = {
		{{.0f, 2.f, .0f},{1,1,1}}, // Top vertex
		{{1.0f,.0f,1.0f},{0,1,0}},
		{{-1.0f,.0f,1.0f},{0,0,1}},
		{{-1.0f,.0f,1.0f},{1,0,0}},
		{{1.0f,.0f,-1.0f},{0,0,1}} // The four base vertices
	};

	// Define face triangles using vertex indices
	Indices = {
		0, 1, 2, // East face
		0, 2, 3, // North face
		0, 3, 4, // West face
		0, 4, 1, // South face
		1, 2, 3,
		3, 4, 1 // Two bottom faces
	};
}