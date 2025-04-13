#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glu.h>

void error_callback(int error, const char* desc);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main() {

	// Initialize GLFW
	if (!glfwInit()) {
		printf("GLFW Initialization: Failed!\n");
	}
	printf("GLFW Initialization: OK!\n");
	glfwSetErrorCallback(error_callback);

	// OpenGL version of device listed within GLView
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

	// Create window
	GLFWwindow* window = glfwCreateWindow(640, 400, "My Window", NULL, NULL);
	if (!window) {
		printf("Window or Context Creation: Failed!\n");
	}
	glfwMakeContextCurrent(window);

	// Bind key callbacks
	glfwSetKeyCallback(window, key_callback);

	// Initialize GLEW
	if (glewInit()) {
		printf("GLEW Initialization: Failed!\n");
	}

	glfwSwapInterval(1);

	// Define shaders
	GLuint Program;
	GLuint vao[1];

	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

	// Define shader sources
	const char* vShaderSrc = "#version 460 \n void main() { gl_position = vec4(0.0, 0.0, 0.0, 1.0};"; // place vertex at position
	const char* fShaderSrc = "#version 460 \n out vec4 color void main() { color = vec4(0.0, 0.3, 1.0, 1.0};"; // color vertex blue

	// Connect source to shaders
	glShaderSource(vShader, 1, &vShaderSrc, NULL);
	glShaderSource(fShader, 1, &fShaderSrc, NULL);

	// Compile shader sources
	glCompileShader(vShader);
	glCompileShader(fShader);

	// Link program
	Program = glCreateProgram();
	glAttachShader(Program, vShader);
	glAttachShader(Program, fShader);
	glLinkProgram(Program);

	glGenVertexArrays(1, vao);
	glBindVertexArray(vao[0]);

	// Display Loop
	while (!glfwWindowShouldClose(window)) {
		glClearColor(1.0, 0.2, 0.3, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		glPointSize(10.f);
		glDrawArrays(GL_POINTS, 0, 1);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Close program
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

void error_callback(int error, const char* description) {
	fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}