#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <iostream>
using namespace std;

#include "graphics_headers.h"
#include "camera.h"
#include "shader.h"
#include "cube.h"

class Graphics
{
  public:
    Graphics(); // constructor
    ~Graphics(); // destructor
    bool Initialize(int width, int height); // set up camera, shader programs, and objects
    void Update(unsigned int dt, glm::vec3 speed); // update/transform any objects
    void Render(); // update view

    Cube* getInteractWith(); // get any interactable objects that are defined

    Cube* getTriangle() { return m_triangle; }

  private:
    std::string ErrorString(GLenum error);
    
    Camera *m_camera;
    Shader *m_shader;

    // Locations of MVP matrices in shader
    GLint m_projectionMatrix;
    GLint m_viewMatrix;
    GLint m_modelMatrix;

    // Locations of vertex attributes in shader
    GLint m_vertPos;
    GLint m_vertCol;

    // Interactable object
    Cube* m_triangle;

};

#endif /* GRAPHICS_H */
