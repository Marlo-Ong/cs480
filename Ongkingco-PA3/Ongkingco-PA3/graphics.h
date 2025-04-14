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
    void Update(double dt, glm::vec3 speed); // update/transform any objects
    void Render(); // update view
    void ComputeTransforms(
        double dt,
        std::vector<float> speed,
        std::vector<float> dist,
        std::vector<float> rotSpeed,
        glm::vec3 rotVector,
        std::vector<float> scale,
        glm::mat4& tmat,
        glm::mat4& rmat,
        glm::mat4& smat);

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

    // Interactable objects
    Cube* m_triangle;

};

#endif /* GRAPHICS_H */
