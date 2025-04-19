#include "graphics.h"

Graphics::Graphics()
{

}

Graphics::~Graphics()
{

}

bool Graphics::Initialize(int width, int height)
{
	// Used for the linux OS
#if !defined(__APPLE__) && !defined(MACOSX)
  // cout << glewGetString(GLEW_VERSION) << endl;
	glewExperimental = GL_TRUE;

	auto status = glewInit();

	// This is here to grab the error that comes from glew init.
	// This error is an GL_INVALID_ENUM that has no effects on the performance
	glGetError();

	//Check for error
	if (status != GLEW_OK)
	{
		std::cerr << "GLEW Error: " << glewGetErrorString(status) << "\n";
		return false;
	}
#endif



	// Init Camera
	m_camera = new Camera();
	if (!m_camera->Initialize(width, height))
	{
		printf("Camera Failed to Initialize\n");
		return false;
	}

	// Set up the shaders
	m_shader = new Shader();
	if (!m_shader->Initialize())
	{
		printf("Shader Failed to Initialize\n");
		return false;
	}

	// Add the vertex shader
	if (!m_shader->AddShader(GL_VERTEX_SHADER))
	{
		printf("Vertex Shader failed to Initialize\n");
		return false;
	}

	// Add the fragment shader
	if (!m_shader->AddShader(GL_FRAGMENT_SHADER))
	{
		printf("Fragment Shader failed to Initialize\n");
		return false;
	}

	// Connect the program
	if (!m_shader->Finalize())
	{
		printf("Program to Finalize\n");
		return false;
	}

	// Populate location bindings of the shader uniform/attribs
	if (!collectShPrLocs()) {
		printf("Some shader attribs not located!\n");
	}

	// Create a pyramid
	m_pyramid = new Pyramid(glm::vec3(-3.f, -2.f, 2.f), 25, 1.5);  // inpit: (pivot location, angle, scale)

	// Create the object
	m_cube = new Object();

	// Create the second cube;
	m_cube2 = new Object(glm::vec3(2.0f, 3.0f, -5.0f));


	//enable depth testing
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	return true;
}

void Graphics::Update(double dt)
{

	glm::mat4 tmat, rmat, smat;
	std::vector<float> speed, dist, rotSpeed, scale;
	glm::vec3 rotVector;

	// Update the object the objects
	speed = {0.3,0.5,0.2};
	dist = { 5., 5., 1.0 };
	rotSpeed = { 1.5f, 1.5f, 1.5f };
	scale = { 1.f, 1.f, 1.f };
	rotVector = glm::vec3(1.0, 1.0, 0.0);
	ComputeTransforms(dt, speed, dist, rotSpeed,rotVector, scale, tmat, rmat, smat);
	if(m_cube!=NULL)
		m_cube->Update(tmat* rmat* smat);
	
	speed = { 0.65,0.0,0.65 };
	dist = { 6., 0., 6. };
	rotSpeed = { 0.75f, 0.75f, 0.0f };
	scale = { .75f, .75f, .75f };
	rotVector = glm::vec3(1.0, .0, 1.0);
	ComputeTransforms(dt, speed, dist, rotSpeed, rotVector, scale, tmat, rmat, smat);
	if(m_cube2!=NULL)
		m_cube2->Update(tmat* rmat* smat);
    
	speed = { 0.35,0.35,0.0 };
	dist = { 3., 3., 0. };
	rotSpeed = { 1.75f, 1.75f, 0.0f };
	scale = { .75f, .75f, .75f };
	rotVector = glm::vec3(.0, 1.0, 0.0);
	ComputeTransforms(dt, speed, dist, rotSpeed, rotVector, scale, tmat, rmat, smat);
	if(m_pyramid!=NULL)
		m_pyramid->Update(tmat* rmat* smat);
}

void Graphics::HierarchicalUpdate(double dt) {
	
	std::vector<float> speed, dist, rotSpeed, scale;
	glm::vec3 rotVector;

	// position of the sun	
	modelStack.push(glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0)));  // world origin
	modelStack.push(modelStack.top());		// The sun origin
	modelStack.top() *= glm::rotate(glm::mat4(1.0f), (float) dt, glm::vec3(0.f, 1.f, 0.f));
	modelStack.top() *= glm::scale(glm::vec3(.75, .75, .75));
	if(m_pyramid!=NULL)
		m_pyramid->Update(modelStack.top());
	modelStack.pop(); // back to sun's positional transformation

	// position of the first planet
	speed = {1., 1., 1.};
	dist = { 6., 0, 6. };
	rotVector = { 1.,1.,1. };
	rotSpeed = { 1., 1., 1. };
	scale = {.5,.5,.5};
	modelStack.top() *= glm::translate(glm::mat4(1.f),
		glm::vec3(cos(speed[0] * dt) * dist[0], sin(speed[1] * dt) * dist[1], sin(speed[2] * dt) * dist[2]));
	modelStack.push(modelStack.top());			// store planet coordinate
	modelStack.top() *= glm::rotate(glm::mat4(1.f), rotSpeed[0] * (float)dt, rotVector);
	modelStack.top() *= glm::scale(glm::vec3(scale[0], scale[1], scale[2]));
	if(m_cube!=NULL)
		m_cube->Update(modelStack.top());
	modelStack.pop();		// back to planet's positional coordinate (remove the rotration, scale)

	// position of the first moon

	speed = { 6, 6, 6 };
	dist = { 1.25, 1.25, 0. };
	rotVector = { 1.,0.,1. };
	rotSpeed = { .25, .25, .25 };
	scale = { .27f, .27f, .27f }; 
	modelStack.top() *= glm::translate(glm::mat4(1.f),
		glm::vec3(cos(speed[0] * dt) * dist[0], sin(speed[1] * dt) * dist[1], sin(speed[2] * dt) * dist[2]));
	modelStack.push(modelStack.top());
	modelStack.top() *= glm::rotate(glm::mat4(1.f), rotSpeed[0] * (float)dt, rotVector);
	modelStack.top() *= glm::scale(glm::vec3(scale[0], scale[1], scale[2]));

	if(m_cube2!=NULL)
		m_cube2->Update(modelStack.top());


	modelStack.pop(); 	//back to the planet coordinate
	
	modelStack.pop(); 	// back to the world coordinate

}


void Graphics::HierarchicalUpdate2(double dt) {

	std::vector<float> speed, dist, rotSpeed, scale;
	glm::vec3 rotVector;
	glm::mat4 localTransform;
	// position of the sun	
	modelStack.push(glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0)));  // sun's coordinate
	localTransform = modelStack.top();		// The sun origin
	localTransform *= glm::rotate(glm::mat4(1.0f), (float)dt, glm::vec3(0.f, 1.f, 0.f));
	localTransform *= glm::scale(glm::vec3(.75, .75, .75));
	if (m_pyramid != NULL)
		m_pyramid->Update(localTransform);

	// position of the first planet
	speed = { 1., 1., 1. };
	dist = { 6., 0, 6. };
	rotVector = { 1.,1.,1. };
	rotSpeed = { 1., 1., 1. };
	scale = { .5,.5,.5 };
	localTransform = modelStack.top();				// start with sun's coordinate
	localTransform *= glm::translate(glm::mat4(1.f),
		glm::vec3(cos(speed[0] * dt) * dist[0], sin(speed[1] * dt) * dist[1], sin(speed[2] * dt) * dist[2]));
	modelStack.push(localTransform);			// store planet-sun coordinate
	localTransform *= glm::rotate(glm::mat4(1.f), rotSpeed[0] * (float)dt, rotVector);
	localTransform *= glm::scale(glm::vec3(scale[0], scale[1], scale[2]));
	if (m_cube != NULL)
		m_cube->Update(localTransform);

	// position of the first moon
	speed = { 6, 6, 6 };
	dist = { 1.25, 1.25, 0. };
	rotVector = { 1.,0.,1. };
	rotSpeed = { .25, .25, .25 };
	scale = { .27f, .27f, .27f };
	localTransform = modelStack.top();
	localTransform *= glm::translate(glm::mat4(1.f),
		glm::vec3(cos(speed[0] * dt) * dist[0], sin(speed[1] * dt) * dist[1], sin(speed[2] * dt) * dist[2]));
	modelStack.push(localTransform);			// store moon-planet-sun coordinate
	localTransform *= glm::rotate(glm::mat4(1.f), rotSpeed[0] * (float)dt, rotVector);
	localTransform *= glm::scale(glm::vec3(scale[0], scale[1], scale[2]));

	if (m_cube2 != NULL)
		m_cube2->Update(localTransform);


	modelStack.pop(); 	// back to the planet coordinate

	modelStack.pop(); 	// back to the sun coordinate

	modelStack.pop();	// empy stack

}


void Graphics::ComputeTransforms(double dt, std::vector<float> speed, std::vector<float> dist, 
	std::vector<float> rotSpeed, glm::vec3 rotVector, std::vector<float> scale, glm::mat4& tmat, glm::mat4& rmat, glm::mat4& smat) {
	tmat = glm::translate(glm::mat4(1.f),
		glm::vec3(cos(speed[0] * dt) * dist[0], sin(speed[1] * dt) * dist[1], sin(speed[2] * dt) * dist[2])
	);
	rmat = glm::rotate(glm::mat4(1.f), rotSpeed[0] * (float)dt, rotVector);
	smat = glm::scale(glm::vec3(scale[0], scale[1], scale[2]));
}

void Graphics::Render()
{
	//clear the screen
	glClearColor(0.5, 0.2, 0.2, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Start the correct program
	m_shader->Enable();

	// Send in the projection and view to the shader (stay the same while camera intrinsic(perspective) and extrinsic (view) parameters are the same
	glUniformMatrix4fv(m_projectionMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetProjection()));
	glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetView()));

	// Render the objects
	if (m_cube != NULL){
		glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_cube->GetModel()));
		m_cube->Render(m_positionAttrib,m_colorAttrib);
	}

	if (m_cube2 != NULL) {
		glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_cube2->GetModel()));
		m_cube2->Render(m_positionAttrib, m_colorAttrib);
	}

	if (m_pyramid != NULL) {
		glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_pyramid->GetModel()));
		m_pyramid->Render(m_positionAttrib, m_colorAttrib);
	}


	// Get any errors from OpenGL
	auto error = glGetError();
	if (error != GL_NO_ERROR)
	{
		string val = ErrorString(error);
		std::cout << "Error initializing OpenGL! " << error << ", " << val << std::endl;
	}
}


bool Graphics::collectShPrLocs() {

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

	// Locate the position vertex attribute
	m_positionAttrib = m_shader->GetAttribLocation("v_position");
	if (m_positionAttrib == -1)
	{
		printf("v_position attribute not found\n");
		return false;
	}

	// Locate the color vertex attribute
	m_colorAttrib = m_shader->GetAttribLocation("v_color");
	if (m_colorAttrib == -1)
	{
		printf("v_color attribute not found\n");
		return false;
	}

	return true;
}

std::string Graphics::ErrorString(GLenum error)
{
	if (error == GL_INVALID_ENUM)
	{
		return "GL_INVALID_ENUM: An unacceptable value is specified for an enumerated argument.";
	}

	else if (error == GL_INVALID_VALUE)
	{
		return "GL_INVALID_VALUE: A numeric argument is out of range.";
	}

	else if (error == GL_INVALID_OPERATION)
	{
		return "GL_INVALID_OPERATION: The specified operation is not allowed in the current state.";
	}

	else if (error == GL_INVALID_FRAMEBUFFER_OPERATION)
	{
		return "GL_INVALID_FRAMEBUFFER_OPERATION: The framebuffer object is not complete.";
	}

	else if (error == GL_OUT_OF_MEMORY)
	{
		return "GL_OUT_OF_MEMORY: There is not enough memory left to execute the command.";
	}
	else
	{
		return "None";
	}
}

