#ifndef CAMERA_H
#define CAMERA_H

#include "graphics_headers.h"

class Camera
{
  public:
    Camera();
    ~Camera();
    bool Initialize(int w, int h);
    glm::mat4 GetProjection();
    glm::mat4 GetView();
    void Update(double dt, glm::vec2 mousePos);
    void SetSpeed(glm::vec3 speed) { this->speed = speed; }

  
  private:
    glm::mat4 projection;
    glm::mat4 view;
    glm::vec3 speed;
    glm::vec3 eyePos = glm::vec3(0, 10, -16);
};

#endif /* CAMERA_H */
