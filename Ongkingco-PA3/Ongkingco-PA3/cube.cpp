#include "cube.h"

Cube::Cube() {
	createVertices();
}

void Cube::createVertices() {

	// Define 8 vertices and colors for cube
	Vertices = {
		{{1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 0.0f}},
		{{1.0f, -1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}}, 
		{{-1.0f, -1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},
		{{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 1.0f}},
		{{1.0f, 1.0f, -1.0f}, {1.0f, 1.0f, 0.0f}},
		{{1.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 1.0f}},
		{{-1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 1.0f}},
		{{-1.0f, 1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}}
	};

	// Define face triangles using vertex indices
	Indices = {
		1, 2, 3,
		7, 6, 5,
		0, 4, 5,
		1, 5, 6,
		6, 7, 3,
		0, 3, 7,
		0, 1, 3,
		4, 7, 5,
		1, 0, 5,
		2, 1, 6,
		2, 6, 3,
		4, 0, 7
	};
}