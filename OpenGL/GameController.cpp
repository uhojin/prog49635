#include "GameController.h"
#include "WindowController.h"
#include "ToolWindow.h"
#include "Fonts.h"
#include "MouseController.h"
#include "ProceduralGeometry.h"

GameController::GameController()
{
	m_shaderColor = { };
	m_shaderDiffuse = { };
	m_shaderPosition = { };
	m_camera = { };
	m_lightPosition = glm::vec3(0.0f, 0.0f, 0.1f);
	m_teapotPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	m_cubes.clear();
}

void GameController::Initialize()
{
	GLFWwindow* window = WindowController::GetInstance().GetWindow();	// Call this first, creates a window required by GLEW
	M_ASSERT(glewInit() == GLEW_OK, "Failed to initialize GLEW.");		// Init GLEW
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);				// Ensure we can capture the escape key
	glClearColor(0.1f, 0.1f, 0.1f, 0.0f);								// grey background
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	srand((unsigned int)time(0));
	// Create a default perspective camera
	m_camera = Camera(WindowController::GetInstance().GetResolution());
	// Initialize mouse controller
	MouseController::Initialize(window);
}

void GameController::RunGame()
{
	// Create and show the ToolWindow
	OpenGL::ToolWindow^ toolWindow = gcnew OpenGL::ToolWindow();
	toolWindow->Show();

	// Create and compile GLSL programs from the shaders
	m_shaderColor.LoadShaders("Color.vertexshader", "Color.fragmentshader");
	m_shaderDiffuse.LoadShaders("Diffuse.vertexshader", "Diffuse.fragmentshader");
	m_shaderPosition.LoadShaders("Position.vertexshader", "Position.fragmentshader");
	m_shaderFont.LoadShaders("Font.vertexshader", "Font.fragmentshader");

	// Initialize Mode 1: Move Light
	// Create sphere for light using OBJ model
	m_lightSphere.Create(&m_shaderColor, "../Assets/Models/sphere.obj");
	m_lightSphere.SetPosition(m_lightPosition);
	m_lightSphere.SetScale(glm::vec3(0.05f, 0.05f, 0.05f));
	m_lightSphere.SetColor(glm::vec3(1.0f, 1.0f, 1.0f));

	// Create teapot for Mode 1 using new teapot_ex2 model
	m_teapotMode1.Create(&m_shaderDiffuse, "../Assets/Models/teapot_ex2.obj");
	m_teapotMode1.SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	m_teapotMode1.SetScale(glm::vec3(0.05f, 0.05f, 0.05f));
	m_teapotMode1.SetCameraPosition(m_camera.GetPosition());

	// Initialize Mode 2: Color By Position
	m_teapotMode2.Create(&m_shaderPosition, "../Assets/Models/teapot_ex2.obj");
	m_teapotMode2.SetPosition(m_teapotPosition);
	m_teapotMode2.SetScale(glm::vec3(0.05f, 0.05f, 0.05f));

	// Initialize Mode 3: Move Cubes To Sphere
	m_sphereMode3.Create(&m_shaderDiffuse, "../Assets/Models/sphere.obj");
	m_sphereMode3.SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	m_sphereMode3.SetScale(glm::vec3(0.05f, 0.05f, 0.05f));
	m_sphereMode3.SetCameraPosition(m_camera.GetPosition());

	Fonts f = Fonts();
	f.Create(&m_shaderFont, "arial.ttf", 48);

	// FPS tracking
	double lastTime = glfwGetTime();
	int frameCount = 0;
	double fps = 0.0;

	// Main game loop
	do
	{
		// Calculate FPS
		double currentTime = glfwGetTime();
		frameCount++;
		if (currentTime - lastTime >= 1.0)
		{
			fps = frameCount / (currentTime - lastTime);
			frameCount = 0;
			lastTime = currentTime;
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Update current mode
		int currentMode = OpenGL::ToolWindow::CurrentMode;

		switch (currentMode)
		{
		case 0: // Move Light
			UpdateMode1();
			RenderMode1();
			break;
		case 1: // Color By Position
			UpdateMode2();
			RenderMode2();
			break;
		case 2: // Move Cubes To Sphere
			UpdateMode3();
			RenderMode3();
			break;
		}

		// Get mouse position
		GLFWwindow* window = WindowController::GetInstance().GetWindow();
		double mouseX, mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);

		// Render FPS counter (top-left)
		string fpsText = "FPS: " + to_string((int)fps);
		f.RenderText(fpsText, 10, 30, 0.5f, { 1.0f, 1.0f, 0.0f });

		// Render mouse position (below FPS)
		string mousePosText = "Mouse Pos: " + to_string((int)mouseX) + ", " + to_string((int)mouseY);
		f.RenderText(mousePosText, 10, 60, 0.5f, { 1.0f, 1.0f, 0.0f });

		// Render UI text based on mode
		if (currentMode == 2)
		{
			// Mode 3: Show cube count (below mouse position)
			string cubeText = "Cubes: " + to_string(m_cubes.size());
			f.RenderText(cubeText, 10, 90, 0.5f, { 1.0f, 1.0f, 0.0f });
		}

		glfwSwapBuffers(WindowController::GetInstance().GetWindow());
		glfwPollEvents();
	} while (glfwGetKey(WindowController::GetInstance().GetWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(WindowController::GetInstance().GetWindow()) == 0);

	// Cleanup
	m_lightSphere.Cleanup();
	m_teapotMode1.Cleanup();
	m_teapotMode2.Cleanup();
	m_sphereMode3.Cleanup();
	for (auto& cube : m_cubes)
	{
		cube.Cleanup();
	}
	m_shaderColor.Cleanup();
	m_shaderDiffuse.Cleanup();
	m_shaderPosition.Cleanup();
	m_shaderFont.Cleanup();
}

// Mode 1: Move Light - Update
void GameController::UpdateMode1()
{
	// Handle reset button
	if (OpenGL::ToolWindow::ResetLightPosition)
	{
		m_lightPosition = glm::vec3(0.0f, 0.0f, 0.1f);
		m_lightSphere.SetPosition(m_lightPosition);
		OpenGL::ToolWindow::ResetLightPosition = false;
	}

	// Handle mouse input for moving light
	if (MouseController::LeftButtonClicked)
	{
		glm::vec2 direction = MouseController::MovementDirection;
		float speed = MouseController::MovementSpeed;

		// Convert 2D direction to 3D movement (move in XY plane)
		// Increased speed multiplier from 0.01f to 0.05f for faster movement
		m_lightPosition.x += direction.x * speed * 0.05f;
		m_lightPosition.y += direction.y * speed * 0.05f;

		m_lightSphere.SetPosition(m_lightPosition);
	}

	// Rotate models around X axis
	static float rotation = 0.0f;
	rotation += 0.001f;
}

// Mode 1: Move Light - Render
void GameController::RenderMode1()
{
	glm::mat4 projectionView = m_camera.GetProjection() * m_camera.GetView();

	// Update light sphere position to match m_lightPosition
	m_lightSphere.SetPosition(m_lightPosition);
	m_lightSphere.SetScale(glm::vec3(0.05f, 0.05f, 0.05f));
	m_lightSphere.SetColor(glm::vec3(1.0f, 1.0f, 1.0f));

	// Set up the Lights vector for the Diffuse shader
	// The Mesh::SetShaderVariables uses the static Mesh::Lights vector
	Mesh::Lights.clear();
	Mesh::Lights.push_back(m_lightSphere);

	// Get trackbar values for specular
	float specularStrength = (float)OpenGL::ToolWindow::SpecularStrength;
	glm::vec3 specularColor(
		OpenGL::ToolWindow::SpecularColorR / 100.0f,
		OpenGL::ToolWindow::SpecularColorG / 100.0f,
		OpenGL::ToolWindow::SpecularColorB / 100.0f
	);

	// Apply specular properties to teapot
	m_teapotMode1.SetSpecularStrength(specularStrength);
	m_teapotMode1.SetSpecularColor(specularColor);
	m_teapotMode1.SetCameraPosition(m_camera.GetPosition());

	// Render light sphere (white, unlit)
	m_lightSphere.Render(projectionView);

	// Render teapot with lighting
	m_teapotMode1.Render(projectionView);
}

// Mode 2: Color By Position - Update
void GameController::UpdateMode2()
{
	// Handle reset button
	if (OpenGL::ToolWindow::ResetTeapotPosition)
	{
		m_teapotPosition = glm::vec3(0.0f, 0.0f, 0.0f);
		m_teapotMode2.SetPosition(m_teapotPosition);
		OpenGL::ToolWindow::ResetTeapotPosition = false;
	}

	// Handle mouse input for moving teapot
	if (MouseController::LeftButtonClicked)
	{
		glm::vec2 direction = MouseController::MovementDirection;
		float speed = MouseController::MovementSpeed;

		// Convert 2D direction to 3D movement (move in XY plane)
		m_teapotPosition.x += direction.x * speed * 0.01f;
		m_teapotPosition.y += direction.y * speed * 0.01f;

		m_teapotMode2.SetPosition(m_teapotPosition);
	}
}

// Mode 2: Color By Position - Render
void GameController::RenderMode2()
{
	glm::mat4 projectionView = m_camera.GetProjection() * m_camera.GetView();

	// Render teapot with position-based coloring
	m_teapotMode2.Render(projectionView);
}

// Mode 3: Move Cubes To Sphere - Update
void GameController::UpdateMode3()
{
	// Handle mouse input for spawning cubes
	// Spawn cubes continuously while mouse button is held down
	if (MouseController::LeftButtonClicked)
	{
		// Spawn a cube at random position
		vector<GLfloat> cubeData = ProceduralGeometry::GenerateCube(0.1f);
		Mesh newCube;
		newCube.CreateFromVertexData(&m_shaderDiffuse, cubeData, "../ex2_asset/MetalFrameWood.jpg");

		// Random position around sphere
		float angle1 = ((float)rand() / RAND_MAX) * 2.0f * 3.14159f;
		float angle2 = ((float)rand() / RAND_MAX) * 3.14159f;
		float distance = 3.0f + ((float)rand() / RAND_MAX) * 2.0f;

		glm::vec3 randomPos(
			distance * sin(angle2) * cos(angle1),
			distance * sin(angle2) * sin(angle1),
			distance * cos(angle2)
		);

		newCube.SetPosition(randomPos);
		newCube.SetScale(glm::vec3(0.5f, 0.5f, 0.5f));
		newCube.SetCameraPosition(m_camera.GetPosition());

		m_cubes.push_back(newCube);
	}

	// Move cubes toward sphere center
	glm::vec3 sphereCenter(0.0f, 0.0f, 0.0f);
	for (int i = m_cubes.size() - 1; i >= 0; i--)
	{
		glm::vec3 cubePos = m_cubes[i].GetPosition();
		glm::vec3 direction = glm::normalize(sphereCenter - cubePos);
		float distance = glm::length(sphereCenter - cubePos);

		// Move cube toward center
		cubePos += direction * 0.005f;
		m_cubes[i].SetPosition(cubePos);

		// Remove cube if it reaches the sphere
		if (distance < 0.15f)
		{
			m_cubes[i].Cleanup();
			m_cubes.erase(m_cubes.begin() + i);
		}
	}
}

// Mode 3: Move Cubes To Sphere - Render
void GameController::RenderMode3()
{
	glm::mat4 projectionView = m_camera.GetProjection() * m_camera.GetView();

	// Use the same light position as Mode 1 (persistent across modes)
	// Render light sphere (white sphere showing light position)
	m_lightSphere.SetPosition(m_lightPosition);
	m_lightSphere.SetScale(glm::vec3(0.15f, 0.15f, 0.15f)); // Make it bigger for visibility in Mode 3
	m_lightSphere.SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
	m_lightSphere.Render(projectionView);

	// Set light for sphere and cubes using the persistent light position
	m_sphereMode3.SetLightPosition(m_lightPosition);
	m_sphereMode3.SetLightColor(glm::vec3(1.0f, 1.0f, 1.0f));

	// Render sphere
	m_sphereMode3.Render(projectionView);

	// Render all cubes
	for (auto& cube : m_cubes)
	{
		cube.SetLightPosition(m_lightPosition);
		cube.SetLightColor(glm::vec3(1.0f, 1.0f, 1.0f));
		cube.Render(projectionView);
	}
}
