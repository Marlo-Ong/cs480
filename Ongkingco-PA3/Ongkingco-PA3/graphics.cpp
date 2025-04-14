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

  // Create the cube
  m_triangle = new Cube();
  m_triangle->Initialize(m_vertPos, m_vertCol);

  
  //enable depth testing
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

    vector<float> speed2 = { 0.35, 0.35, 0.0 };
    vector<float> dist = { 3., 3., 0.0 };
    vector<float> rotSpeed = { 0.75, 0.75, 0.0 };
    glm::vec3 rotVector = { 0, 1, 0.0 };
    vector<float> scale = { 1, 1, 1 };

    ComputeTransforms(dt, speed2, dist, rotSpeed, rotVector, scale, tmat, smat, rmat);

    // Update the solar system
    sun->Update(tmat * rmat * smat);
  //planet->Update(dt);
  //moon->Update(dt);

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

  // Render the cube
  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_triangle->GetModel()));
  m_triangle->Render(m_vertPos,m_vertCol);



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
