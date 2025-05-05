#include "camera.h"
#include "glm/ext.hpp"

Camera::Camera()
{

}

Camera::~Camera()
{

}

bool Camera::Initialize(int w, int h)
{
  //--Init the view and projection matrices
  view = glm::lookAt( eyePos, //Eye Position
                      glm::vec3(0.0, 0.0, 0.0), //Focus point
                      glm::vec3(0.0, 1.0, 0.0)); //Positive Y is up

  width = float(w);
  height = float(h);

  projection = glm::perspective( glm::radians(40.f), //the FoV typically 90 degrees is good which is what this is set to
                                 width/height, //Aspect Ratio, so Circles stay Circular
                                 0.01f, //Distance to the near plane, normally a small value like this
                                 100.0f); //Distance to the far plane, 
  return true;
}

void Camera::Update(double dt, glm::vec2 mousePos) {
    // calculate the delta mouse pos instead of absolute mouse pos
    static float lastX, lastY;
    float deltaYaw = mouseSensitivity * (mousePos.x - lastX); // horizontal change
    float deltaPitch = mouseSensitivity * (lastY - mousePos.y); // vertical change
    lastX = mousePos.x;
    lastY = mousePos.y;

    // update and constrain rotation using mouse change
    yaw = glm::clamp(yaw + deltaYaw, -120.f, -60.f);
    pitch = glm::clamp(pitch + deltaPitch, -45.f, -15.f);

    // calculate the forward vector given pitch and yaw
    glm::vec3 forward;
    forward.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    forward.y = sin(glm::radians(pitch));
    forward.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    forward = glm::normalize(forward);

    // update and constrain horizontal translation
    eyePos += speed.x * mouseSensitivity * (float)dt;

    // translate camera based on forward vector
    eyePos += forward * speed.y * mouseSensitivity * (float)dt;


    // update the view matrix
    view = glm::lookAt(
        eyePos, // position of eye
        eyePos + forward, // target point in front of eye
        glm::vec3(0.0, 1.0, 0.0)); // positive Y is up

    // update the projection matrix with zoom
    projection = glm::perspective(glm::radians(zoom), // changed by scroll wheel
        width / height,
        0.01f,
        100.0f);
}

glm::mat4 Camera::GetProjection()
{
  return projection;
}

glm::mat4 Camera::GetView()
{
  return view;
}


