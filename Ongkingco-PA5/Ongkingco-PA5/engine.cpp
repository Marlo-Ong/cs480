
#include "engine.h"

Engine::Engine(const char* name, int width, int height)
{
  m_WINDOW_NAME = name;
  m_WINDOW_WIDTH = width;
  m_WINDOW_HEIGHT = height;

}


Engine::~Engine()
{
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
  glfwSetScrollCallback(m_window->getWindow(), scrollCallback);

  // No errors
  return true;
}

void Engine::Run()
{
  m_running = true;
  glfwSetInputMode(m_window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  
  while (!glfwWindowShouldClose(m_window->getWindow()))
  {
      ProcessInput();
      Display(m_window->getWindow(), glfwGetTime());
      glfwPollEvents();
  }
  m_running = false;

}

void Engine::ProcessInput()
{
    if (glfwGetKey(m_window->getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(m_window->getWindow(), true);

    // Get mouse position
    double x, y;
    glfwGetCursorPos(m_window->getWindow(), &x, &y);
    m_graphics->SetMousePos(glm::vec2(x, y));

    if (scrollCallbackCalledThisFrame) {
        m_graphics->GetCamera()->IncreaseZoom(zoomOffset);
        scrollCallbackCalledThisFrame = false;
    }

    // (Stop translation key if no movement key is pressed)
    if (glfwGetKey(m_window->getWindow(), GLFW_KEY_W) == GLFW_RELEASE &&
        glfwGetKey(m_window->getWindow(), GLFW_KEY_A) == GLFW_RELEASE &&
        glfwGetKey(m_window->getWindow(), GLFW_KEY_S) == GLFW_RELEASE &&
        glfwGetKey(m_window->getWindow(), GLFW_KEY_D) == GLFW_RELEASE)
        m_graphics->GetCamera()->SetSpeed(glm::vec3(0));

    // Translate on the camera positive-Y axis when up is pressed
    if (glfwGetKey(m_window->getWindow(), GLFW_KEY_W) == GLFW_PRESS)
        m_graphics->GetCamera()->SetSpeed(glm::vec3(0., .1, 0.));

    // Translate on the camera negative-Y axis when down is pressed
    if (glfwGetKey(m_window->getWindow(), GLFW_KEY_S) == GLFW_PRESS)
        m_graphics->GetCamera()->SetSpeed(glm::vec3(0., -.1, 0.));

    // Translate on the camera negative-X axis when left is pressed
    if (glfwGetKey(m_window->getWindow(), GLFW_KEY_A) == GLFW_PRESS)
        m_graphics->GetCamera()->SetSpeed(glm::vec3(-.1, 0., 0.));

    // Translate on the camera positive-X axis when right is pressed
    if (glfwGetKey(m_window->getWindow(), GLFW_KEY_D) == GLFW_PRESS)
        m_graphics->GetCamera()->SetSpeed(glm::vec3(.1, 0., 0.));
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

    m_graphics->Render();
    m_window->Swap();

    // update graphics -> updates model
    //m_graphics->Update(time);
    m_graphics->HierarchicalUpdate2(time);
}

static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    zoomOffset = yoffset;
    scrollCallbackCalledThisFrame = true;
}
