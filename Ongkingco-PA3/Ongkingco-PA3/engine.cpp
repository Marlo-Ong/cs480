
#include "engine.h"

Engine::Engine(const char* name, int width, int height)
{
  // Set window options
  m_WINDOW_NAME = name;
  m_WINDOW_WIDTH = width;
  m_WINDOW_HEIGHT = height;

}


Engine::~Engine()
{
  // Destroy window
  delete m_window;
  delete m_graphics;
  m_window = NULL;
  m_graphics = NULL;
}


bool Engine::Initialize()
{
  // Start a window
  m_window = new Window(m_WINDOW_NAME, &m_WINDOW_WIDTH, &m_WINDOW_HEIGHT);
  if(!m_window->Initialize())
  {
    printf("The window failed to initialize.\n");
    return false;
  }

  // Start the graphics
  m_graphics = new Graphics();
  if(!m_graphics->Initialize(m_WINDOW_WIDTH, m_WINDOW_HEIGHT))
  {
    printf("The graphics failed to initialize.\n");
    return false;
  }

  // No errors
  return true;
}


void Engine::Run()
{
  m_running = true;

  // Run main loop if current window should not be closed
  while (!glfwWindowShouldClose(m_window->getWindow()))
  {
      // Disable input for this assignment:
      //ProcessInput(); // check for user movement input

      Display(m_window->getWindow(), glfwGetTime()); // update the view
      glfwPollEvents(); // check for window input and window changes
  }
  m_running = false;

}

void Engine::ProcessInput()
{
    //// Close window when pressing ESC key
    //if (glfwGetKey(m_window->getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
    //    glfwSetWindowShouldClose(m_window->getWindow(), true);

    //// (Stop translation key if no movement key is pressed)
    //if (glfwGetKey(m_window->getWindow(), GLFW_KEY_UP) == GLFW_RELEASE &&
    //    glfwGetKey(m_window->getWindow(), GLFW_KEY_DOWN) == GLFW_RELEASE &&
    //    glfwGetKey(m_window->getWindow(), GLFW_KEY_LEFT) == GLFW_RELEASE &&
    //    glfwGetKey(m_window->getWindow(), GLFW_KEY_RIGHT) == GLFW_RELEASE)
    //    m_graphics->getTriangle()->setSpeed(glm::vec3(0., 0., 0.));

    //// Translate on the cube's positive-Y axis when up arrow is pressed
    //if (glfwGetKey(m_window->getWindow(), GLFW_KEY_UP) == GLFW_PRESS)
    //    m_graphics->getTriangle()->setSpeed(glm::vec3(0., .1, 0.));

    //// Translate on the cube's negative-Y axis when down arrow is pressed
    //if (glfwGetKey(m_window->getWindow(), GLFW_KEY_DOWN) == GLFW_PRESS)
    //    m_graphics->getTriangle()->setSpeed(glm::vec3(0., -.1, 0.));

    //// Translate on the cube's negative-X axis when left arrow is pressed
    //if (glfwGetKey(m_window->getWindow(), GLFW_KEY_LEFT) == GLFW_PRESS)
    //    m_graphics->getTriangle()->setSpeed(glm::vec3(-.1, 0., 0.));

    //// Translate on the cube's positive-X axis when right arrow is pressed
    //if (glfwGetKey(m_window->getWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS)
    //    m_graphics->getTriangle()->setSpeed(glm::vec3(.1, 0., 0.));


    //// EXTRA CREDIT (Ugrad section)

    //// (Stop rotation if no rotation key is pressed)
    //if (glfwGetKey(m_window->getWindow(), GLFW_KEY_P) == GLFW_RELEASE &&
    //    glfwGetKey(m_window->getWindow(), GLFW_KEY_O) == GLFW_RELEASE)
    //    m_graphics->getTriangle()->setAngularSpeed(glm::vec3(0., 0., 0.));

    //// Rotate object clockwise along z-axis
    //if (glfwGetKey(m_window->getWindow(), GLFW_KEY_P) == GLFW_PRESS)
    //    m_graphics->getTriangle()->setAngularSpeed(glm::vec3(0., 0., -0.1f));

    //// Rotate object counter-clockwise along z-axis
    //if (glfwGetKey(m_window->getWindow(), GLFW_KEY_O) == GLFW_PRESS)
    //    m_graphics->getTriangle()->setAngularSpeed(glm::vec3(0., 0., 0.1f));
}

unsigned int Engine::getDT()
{
  //long long TimeNowMillis = GetCurrentTimeMillis();
  //assert(TimeNowMillis >= m_currentTimeMillis);
  //unsigned int DeltaTimeMillis = (unsigned int)(TimeNowMillis - m_currentTimeMillis);
  //m_currentTimeMillis = TimeNowMillis;
  //return DeltaTimeMillis;
    return glfwGetTime();
}

long long Engine::GetCurrentTimeMillis()
{
  //timeval t;
  //gettimeofday(&t, NULL);
  //long long ret = t.tv_sec * 1000 + t.tv_usec / 1000;
  //return ret;
    return (long long) glfwGetTime();
}

void Engine::Display(GLFWwindow* window, double time) {

    m_graphics->Render(); // update view

    m_window->Swap(); // swap buffers

    m_graphics->Update(time, speed); // perform any object updates
}
