#include "GameController.h"
#include "WindowController.h"
#include "ToolWindow.h"

GameController::GameController()
{
	m_shader = { };
	m_mesh = { };
}

void GameController::Initialize()
{
	GLFWwindow* window = WindowController::GetInstance().GetWindow();	// Call this first, creates a window required by GLEW
	M_ASSERT(glewInit() == GLEW_OK, "Failed to initialize GLEW.");		// Init GLEW
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);				// Ensure we can capture the escape key
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);								// Dark Blue background
}

void GameController::RunGame()
{
	// Show the C++/CLI tool window
	OpenGL::ToolWindow^ window = gcnew OpenGL::ToolWindow();
	window->Show();

	// Create and compile out GLSL program grom the shaders
	m_shader = Shader();
	m_shader.LoadShaders(
		"SimpleVertexShader.vertexshader",
		"SimpleFragmentShader.fragmentshader"
	);

	m_mesh = Mesh();
	m_mesh.Create(&m_shader);

	//GLFWwindow* win = WindowController::GetInstance().GetWindow();
	do
	{
		System::Windows::Forms::Application::DoEvents(); // Handle C++/CLI form events
		glClear(GL_COLOR_BUFFER_BIT);	// Clear screen
		m_mesh.Render();
		//glfwSwapBuffers(win);			// Swap the front and back buffers
		glfwSwapBuffers(WindowController::GetInstance().GetWindow());			// Swap the front and back buffers
		glfwPollEvents();
		//} while (glfwGetKey(win, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(win) == 0); // CHeck if ESC was pressed or window was closed
	} while (glfwGetKey(WindowController::GetInstance().GetWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(WindowController::GetInstance().GetWindow()) == 0); // Check if window was closed
	m_mesh.Cleanup();
	m_shader.Cleanup();
}
