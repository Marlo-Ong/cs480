#ifndef ENGINE_H
#define ENGINE_H


#include <assert.h>
#include "window.h"
#include "graphics.h"

static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
static double zoomOffset;
static bool scrollCallbackCalledThisFrame;

class Engine
{
  public:
    Engine(const char*  name, int width, int height);
    
    ~Engine();
    bool Initialize();
    void Run();
    void ProcessInput();
    unsigned int getDT();
    long long GetCurrentTimeMillis();
    void Display(GLFWwindow*, double);
  
  private:
    // Window related variables
    Window *m_window;    
    const char* m_WINDOW_NAME;
    int m_WINDOW_WIDTH;
    int m_WINDOW_HEIGHT;
    bool m_FULLSCREEN;


    Graphics *m_graphics;

    bool m_running;
};

#endif // ENGINE_H
