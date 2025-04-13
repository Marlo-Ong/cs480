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

	// TO DO: Make the camera to be placed at location (10, 12, -20), point at origin, and the right-handed Y-up coordinate
	view = glm::lookAt(glm::vec3(1.0, 12.0, 20.0), //Eye Position
		glm::vec3(0.0, 0.0, 0.0), //Focus point
		glm::vec3(0.0, 1.0, 0.0)); //Positive Y is up

	projection = glm::perspective(glm::radians(45.f), //the FoV typically 90 degrees is good which is what this is set to
		float(w) / float(h), //Aspect Ratio, so Circles stay Circular
		0.01f, //Distance to the near plane, normally a small value like this
		100.0f); //Distance to the far plane, 

	// To DO:
	//Change your camera to orthographic
	//projection = glm::ortho(float(-w / 100), float(w / 100), -float(h/100), float(h/100), -20.f, 20.f);

	return true;
}

glm::mat4 Camera::GetProjection()
{
	return projection;
}

glm::mat4 Camera::GetView()
{
	return view;
}


