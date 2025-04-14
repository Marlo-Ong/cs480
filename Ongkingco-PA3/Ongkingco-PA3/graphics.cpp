#include "graphics.h"

Graphics::Graphics()
{

}

Graphics::~Graphics()
{

}

bool Graphics::Initialize(int width, int height)
{

  // For OpenGL 3

  // Init Camera
  m_camera = new Camera();
  if(!m_camera->Initialize(width, height))
  {
    printf("Camera Failed to Initialize\n");
    return false;
  }

  // Set up the shaders
  m_shader = new Shader();
  if(!m_shader->Initialize())
  {
    printf("Shader Failed to Initialize\n");
    return false;
  }

  // Add the vertex shader
  if(!m_shader->AddShader(GL_VERTEX_SHADER))
  {
    printf("Vertex Shader failed to Initialize\n");
    return false;
  }

  // Add the fragment shader
  if(!m_shader->AddShader(GL_FRAGMENT_SHADER))
  {
    printf("Fragment Shader failed to Initialize\n");
    return false;
  }

  // Connect the program
  if(!m_shader->Finalize())
  {
    printf("Program to Finalize\n");
    return false;
  }

  // Locate the projection matrix in the shader
  m_projectionMatrix = m_shader->GetUniformLocation("projectionMatrix");
  if (m_projectionMatrix == INVALID_UNIFORM_LOCATION) 
  {
    printf("m_projectionMatrix not found\n");
    return false;
  }

  // Locate the view matrix in the shader
  m_viewMatrix = m_shader->GetUniformLocation("viewMatrix");
  if (m_viewMatrix == INVALID_UNIFORM_LOCATION) 
  {
    printf("m_viewMatrix not found\n");
    return false;
  }

  // Locate the model matrix in the shader
  m_modelMatrix = m_shader->GetUniformLocation("modelMatrix");
  if (m_modelMatrix == INVALID_UNIFORM_LOCATION) 
  {
    printf("m_modelMatrix not found\n");
    return false;
  }

  // Find where vertex attributes are in shader
  m_vertPos = m_shader->GetAttribLocation("v_position");
  m_vertCol = m_shader->GetAttribLocation("v_color");

  // Create the solar system
  sun = new Pyramid();
  planet = new Cube();
  moon = new Cube();

  sun->Initialize(m_vertPos, m_vertCol);
  planet->Initialize(m_vertPos, m_vertCol);
  moon->Initialize(m_vertPos, m_vertCol);

  // EXTRA CREDIT Ugrad: Add additional moon.
  moon2 = new Pyramid();
  moon2->Initialize(m_vertPos, m_vertCol);

  // enable depth testing
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  return true;
}

void Graphics::ComputeTransforms(
    double dt,
    std::vector<float> speed,
    std::vector<float> dist,
    std::vector<float> rotSpeed,
    glm::vec3 rotVector,
    std::vector<float> scale,
    glm::mat4& tmat,
    glm::mat4& rmat,
    glm::mat4& smat) {

    tmat = glm::translate(glm::mat4(1.f), glm::vec3(
        cos(speed[0] * dt) * dist[0],
        sin(speed[1] * dt) * dist[1],
        sin(speed[2] * dt) * dist[2]));

    rmat = glm::rotate(glm::mat4(1.f), rotSpeed[0] * (float)dt, rotVector);
    smat = glm::scale(glm::vec3(scale[0], scale[1], scale[2]));
}

void Graphics::Update(double dt, glm::vec3 speed)
{
  glm::mat4 tmat;
  glm::mat4 rmat;
  glm::mat4 smat;
  std::stack<glm::mat4> tStack;

  // Sun parameters
  vector<float> speed1 = {0, 0, 0};
  vector<float> dist1 = {0, 0, 0};
  vector<float> rotSpeed1 = {1, 0, 0};
  glm::vec3 rotVector1 = {0, 1, 0};
  vector<float> scale1 = {2, 2, 2};

  // Planet parameters
  vector<float> speed2 = {1, 0, 1};
  vector<float> dist2 = {8, 0, 8};
  vector<float> rotSpeed2 = {2, 0, 0};
  glm::vec3 rotVector2 = {0, 1, 0};
  vector<float> scale2 = {1, 1, 1};

  // Moon 1 parameters
  vector<float> speed3 = {3, 3, 0};
  vector<float> dist3 = {3, 3, 0};
  vector<float> rotSpeed3 = {3, 3, 0};
  glm::vec3 rotVector3 = {1, 1, 0};
  vector<float> scale3 = {.5, .5, .5};

  // Moon 2 parameters
  vector<float> speed4 = {2, 2, 0};
  vector<float> dist4 = {5, 5, 0};
  vector<float> rotSpeed4 = {2, 2, 0.0};
  glm::vec3 rotVector4 = {1, 1, 0};
  vector<float> scale4 = {.5, .5, .5};

  // Update sun
  ComputeTransforms(dt, speed1, dist1, rotSpeed1, rotVector1, scale1, tmat, smat, rmat);
  sun->Update(sun->GetModel() * tmat * rmat * smat);
  tStack.push(tmat);

  // Update planet
  ComputeTransforms(dt, speed2, dist2, rotSpeed2, rotVector2, scale2, tmat, smat, rmat);
  planet->Update(tStack.top() * tmat * rmat * smat);
  tStack.push(tmat);

  // Update moon 1
  ComputeTransforms(dt, speed3, dist3, rotSpeed3, rotVector3, scale3, tmat, smat, rmat);
  moon->Update(tStack.top() * tmat * rmat * smat);
  tStack.push(tmat);
  tStack.pop(); // consider this moon as a "leaf" node

  // Update moon 2
  ComputeTransforms(dt, speed4, dist4, rotSpeed4, rotVector4, scale4, tmat, smat, rmat);
  moon2->Update(tStack.top() * tmat * rmat * smat);
  tStack.push(tmat);
  tStack.pop();

  tStack.pop(); // pop planet
  tStack.pop(); // pop sun
}

void Graphics::Render()
{
  //clear the screen
  glClearColor(0.5, 0.2, 0.2, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Start the correct program
  m_shader->Enable();

  // Send in the projection and view to the shader
  glUniformMatrix4fv(m_projectionMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetProjection()));
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetView()));

  // Render the solar system
  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(sun->GetModel()));
  sun->Render(m_vertPos, m_vertCol);

  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(planet->GetModel()));
  planet->Render(m_vertPos, m_vertCol);

  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(moon->GetModel()));
  moon->Render(m_vertPos, m_vertCol);

  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(moon2->GetModel()));
  moon2->Render(m_vertPos, m_vertCol);

  // Get any errors from OpenGL
  auto error = glGetError();
  if ( error != GL_NO_ERROR )
  {
    string val = ErrorString( error );
    std::cout<< "Error initializing OpenGL! " << error << ", " << val << std::endl;
  }
}

// Define GL global error messages
std::string Graphics::ErrorString(GLenum error)
{
  if(error == GL_INVALID_ENUM)
  {
    return "GL_INVALID_ENUM: An unacceptable value is specified for an enumerated argument.";
  }

  else if(error == GL_INVALID_VALUE)
  {
    return "GL_INVALID_VALUE: A numeric argument is out of range.";
  }

  else if(error == GL_INVALID_OPERATION)
  {
    return "GL_INVALID_OPERATION: The specified operation is not allowed in the current state.";
  }

  else if(error == GL_INVALID_FRAMEBUFFER_OPERATION)
  {
    return "GL_INVALID_FRAMEBUFFER_OPERATION: The framebuffer cube is not complete.";
  }

  else if(error == GL_OUT_OF_MEMORY)
  {
    return "GL_OUT_OF_MEMORY: There is not enough memory left to execute the command.";
  }
  else
  {
    return "None";
  }
}
