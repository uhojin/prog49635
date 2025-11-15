#include "GameController.h"
#include "WindowController.h"
#include "ToolWindow.h"

GameController::GameController()
{
	m_shaderColor = { };
	m_shaderDiffuse = { };
	m_camera = { };
	m_meshBoxes.clear();
	m_meshLight = { };
}

void GameController::Initialize()
{
	GLFWwindow* window = WindowController::GetInstance().GetWindow();	// Call this first, creates a window required by GLEW
	M_ASSERT(glewInit() == GLEW_OK, "Failed to initialize GLEW.");		// Init GLEW
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);				// Ensure we can capture the escape key
	glClearColor(0.1f, 0.1f, 0.1f, 0.0f);								// grey background
	glEnable(GL_DEPTH_TEST);
	srand(time(0));
	// Create a default perspective camera
	m_camera = Camera(WindowController::GetInstance().GetResolution());
}

void GameController::RunGame()
{
	
	// Create and compile out GLSL program from the shaders
	m_shaderColor = Shader();
	m_shaderColor.LoadShaders(
		"Color.vertexshader",
		"Color.fragmentshader"
	);
	
	m_shaderDiffuse = Shader();
	m_shaderDiffuse.LoadShaders(
		"Diffuse.vertexshader",
		"Diffuse.fragmentshader"
	);

	// Create meshes
	m_meshLight = Mesh();
	m_meshLight.Create(&m_shaderColor);
	m_meshLight.SetPosition({ 0.5f, 0.0f, -0.5f });
	m_meshLight.SetScale({ 0.1f, 0.1f, 0.1f });

	for (int count = 0; count < 4; count++)
	{
		Mesh m = Mesh();
		m.Create(&m_shaderColor);
		m.SetPosition({ 0.5f + (float)count / 10.0f, 0.0f, -0.5f });
		m.SetColor({ glm::linearRand(0.0f, 1.0f), glm::linearRand(0.0f, 1.0f), glm::linearRand(0.0f, 1.0f) });
		m.SetScale({ 0.1f, 0.1f, 0.1f });
		Mesh::Lights.push_back(m);
	}

	for (int col = 0; col < 10; col++)
	{
		for (int count = 0; count < 10; count++)
		{
		Mesh box = Mesh();
		box.Create(&m_shaderDiffuse);
		box.SetLightColor({ 1.0f, 1.0f, 1.0f });
		box.SetLightPosition(m_meshLight.GetPosition());
		box.SetCameraPosition(m_camera.GetPosition());
		box.SetScale({ 0.1f, 0.1f, 0.1f });
		box.SetPosition({
			0.0, -0.5f + (float)count / 10.0f, -0.2f + (float)col / 10.0f
			});
		m_meshBoxes.push_back(box);
		}
	}

	//GLFWwindow* win = WindowController::GetInstance().GetWindow();
	do
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the screen and depth buffer
		for (unsigned int count = 0; count < m_meshBoxes.size(); count++)
		{
			m_meshBoxes[count].Render(m_camera.GetProjection() * m_camera.GetView());
		}
		m_meshLight.Render(m_camera.GetProjection() * m_camera.GetView());
		glfwSwapBuffers(WindowController::GetInstance().GetWindow());			// Swap the front and back buffers
		glfwPollEvents();

	} while (glfwGetKey(WindowController::GetInstance().GetWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(WindowController::GetInstance().GetWindow()) == 0); // Check if window was closed
	
	m_meshLight.Cleanup();
	for (unsigned int count = 0; count < m_meshBoxes.size(); count++)
	{
		m_meshBoxes[count].Cleanup();
	}
	m_shaderDiffuse.Cleanup();
	m_shaderColor.Cleanup();
}
