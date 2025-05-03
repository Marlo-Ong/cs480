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
    float yaw = 0.f;
    float pitch = 0.f;
    const float mouseSensitivity = 0.05f;

    glm::vec3 startingEyePos = glm::vec3(0, 10, 16);
    glm::vec3 eyePos = startingEyePos;
};

#endif /* CAMERA_H */
