#include "window.h"

using namespace std;

Window::Window(const char* name, int* width, int* height)
{
  gWindow = NULL;

  if (!glfwInit())
  {
      const char* err;
      glfwGetError(&err);
      printf("GLFW failed to initialize: %s\n", err);
      gWindow = NULL;
  }

  // Start OpenGL for GLFW

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

  // Create window
  gWindow = glfwCreateWindow(*width, *height, name, NULL, NULL);

  glfwMakeContextCurrent(gWindow);

  this->Initialize();
}

Window::~Window()
{

  glfwDestroyWindow(gWindow);
  gWindow = NULL;
  glfwTerminate();
}

bool Window::Initialize()
{
    // Start SDL
    if (glewInit() != GLEW_OK) { exit(EXIT_FAILURE); }
    glfwSwapInterval(1);


    // Any other Window Initialization goes here

    return true;
}

void Window::Swap()
{
    glfwSwapBuffers(gWindow);
}
