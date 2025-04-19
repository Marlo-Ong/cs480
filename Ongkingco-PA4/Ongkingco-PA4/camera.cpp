#include "camera.h"

Camera::Camera()
{

}

Camera::~Camera()
{

}

bool Camera::Initialize(int w, int h)
{
  //--Init the view and projection matrices
  //  if you will be having a moving camera the view matrix will need to more dynamic
  //  ...Like you should update it before you render more dynamic 
  //  for this project having them static will be fine
  view = glm::lookAt( eyePos, //Eye Position
                      glm::vec3(0.0, 0.0, 0.0), //Focus point
                      glm::vec3(0.0, 1.0, 0.0)); //Positive Y is up

  projection = glm::perspective( glm::radians(40.f), //the FoV typically 90 degrees is good which is what this is set to
                                 float(w)/float(h), //Aspect Ratio, so Circles stay Circular
                                 0.01f, //Distance to the near plane, normally a small value like this
                                 100.0f); //Distance to the far plane, 
  return true;
}

void Camera::Update(double dt, glm::vec2 mousePos) {
    glm::vec2 clampedPos = glm::clamp(mousePos, glm::vec2(-2), glm::vec2(2));

    view = glm::lookAt(eyePos, //Eye Position
        glm::vec3(clampedPos.x, clampedPos.y, 0.0), //Focus point
        glm::vec3(0.0, 1.0, 0.0));

	view = glm::translate(view, speed);
}

glm::mat4 Camera::GetProjection()
{
  return projection;
}

glm::mat4 Camera::GetView()
{
  return view;
}


