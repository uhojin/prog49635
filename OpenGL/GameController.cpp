#include "GameController.h"
#include "WindowController.h"
#include "ToolWindow.h"
#include "Fonts.h"
#include "MouseController.h"
#include "ProceduralGeometry.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

GameController::GameController()
{
	m_shaderColor = { };
	m_shaderDiffuse = { };
	m_shaderPosition = { };
	m_camera = { };
	m_lightPosition = glm::vec3(0.0f, 0.0f, 2.0f);
	m_transformPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	m_transformRotation = glm::vec3(1.0f, 0.0f, 0.0f);
	m_transformScale = glm::vec3(0.002f, 0.002f, 0.002f);

	// Store initial transform state for reset
	m_initialTransformPosition = m_transformPosition;
	m_initialTransformRotation = m_transformRotation;
	m_initialTransformScale = m_transformScale;
	m_previousMode = 0;
	m_rotationAtClick = glm::vec3(0.0f, 0.0f, 0.0f);
	m_scaleAtClick = glm::vec3(0.0f, 0.0f, 0.0f);
	m_wasLeftButtonDown = false;
	m_wasMiddleButtonDown = false;
	m_cameraViewSaved = false;
}

void GameController::Initialize()
{
	GLFWwindow* window = WindowController::GetInstance().GetWindow();	// Call this first, creates a window required by GLEW
	M_ASSERT(glewInit() == GLEW_OK, "Failed to initialize GLEW.");		// Init GLEW
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);				// Ensure we can capture the escape key
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);								// black background
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
	m_shaderPost.LoadShaders("Postprocessor.vertexshader", "Postprocessor.fragmentshader");
	m_shaderSkybox.LoadShaders("Skybox.vertexshader", "Skybox.fragmentshader");

	// Initialize Mode 0: Move Light
	// Create sphere for light using OBJ model
	m_lightSphere.Create(&m_shaderColor, "../Assets/Models/sphere.obj");
	m_lightSphere.SetPosition(m_lightPosition);
	m_lightSphere.SetScale(glm::vec3(0.05f, 0.05f, 0.05f));
	m_lightSphere.SetColor(glm::vec3(1.0f, 1.0f, 1.0f));

	// Create Fighter for Mode 0 with normal mapping
	m_fighterMode1.Create(&m_shaderDiffuse, "../Assets/Models/Fighter.obj");
	m_fighterMode1.SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	m_fighterMode1.SetScale(glm::vec3(0.002f, 0.002f, 0.002f));
	m_fighterMode1.SetCameraPosition(m_camera.GetPosition());

	// Initialize Mode 1: Transform with Fighter
	m_fighterMode2.Create(&m_shaderDiffuse, "../Assets/Models/Fighter.obj");
	m_fighterMode2.SetPosition(m_transformPosition);
	m_fighterMode2.SetScale(m_transformScale);
	m_fighterMode2.SetCameraPosition(m_camera.GetPosition());

	// Initialize Mode 2: Water Scene with Fish model
	m_waterPlane.Create(&m_shaderDiffuse, "../Assets/Models/Fish.obj");
	m_waterPlane.SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	m_waterPlane.SetRotation(glm::vec3(0.0f, 180.0f, 0.0f));
	m_waterPlane.SetScale(glm::vec3(0.02f, 0.02f, 0.02f));
	m_waterPlane.SetRotationEnabled(false);  // Disable automatic rotation
	m_waterPlane.SetCameraPosition(m_camera.GetPosition());

	// Initialize PostProcessor for Water Scene
	m_postProcessor.Create(&m_shaderPost);

	// Initialize Mode 3: Space Scene
	// Create skybox with new space textures from FinalProjectAssets
	m_skybox.Create(&m_shaderSkybox, "../Assets/Models/Skybox.obj", {
		"../FinalProjectAssets/ZipAssets/Skybox/right.jpg",
		"../FinalProjectAssets/ZipAssets/Skybox/left.jpg",
		"../FinalProjectAssets/ZipAssets/Skybox/top.jpg",
		"../FinalProjectAssets/ZipAssets/Skybox/bottom.jpg",
		"../FinalProjectAssets/ZipAssets/Skybox/front.jpg",
		"../FinalProjectAssets/ZipAssets/Skybox/back.jpg"
	});

	// Create fighter at origin facing away from camera
	m_spaceFighter.Create(&m_shaderDiffuse, "../Assets/Models/Fighter.obj");
	m_spaceFighter.SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	m_spaceFighter.SetRotation(glm::vec3(0.0f, 180.0f, 0.0f)); // Facing away
	m_spaceFighter.SetScale(glm::vec3(0.002f, 0.002f, 0.002f));
	m_spaceFighter.SetRotationEnabled(false); // Disable auto-rotation
	m_spaceFighter.SetCameraPosition(m_camera.GetPosition());

	// Create asteroid mesh (will render multiple times with different transforms)
	m_asteroids.Create(&m_shaderDiffuse, "../Assets/Models/asteroid.obj");
	m_asteroids.SetRotationEnabled(false); // Disable auto-rotation, use random rotations
	m_asteroids.SetCameraPosition(m_camera.GetPosition());

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

		// Update mouse controller EVERY frame
		GLFWwindow* window = WindowController::GetInstance().GetWindow();
		MouseController::Update(window);

		// Update current mode
		int currentMode = OpenGL::ToolWindow::CurrentMode;

		// Restore camera when leaving space scene (mode 3)
		static int previousMode = -1;
		if (previousMode == 3 && currentMode != 3 && m_cameraViewSaved)
		{
			m_camera.SetView(m_originalCameraView);
			m_camera.SetPosition(m_originalCameraPosition);
			m_cameraViewSaved = false;
		}
		previousMode = currentMode;

		switch (currentMode)
		{
		case 0: // Move Light
			UpdateMode1();
			RenderMode1();
			break;
		case 1: // Transform
			UpdateMode2();
			RenderMode2();
			break;
		case 2: // Water Scene
			UpdateMode3();
			RenderMode3(&f, fps);  // Pass fonts and fps for rendering inside framebuffer
			break;
		case 3: // Space Scene
			UpdateMode4();
			RenderMode4();
			break;
		}

		// Render text for modes 0, 1, and 3
		// Mode 2 (Water Scene) renders text inside RenderMode3() for post-processing
		if (currentMode != 2)
		{
			// Get mouse position
			double mouseX, mouseY;
			glfwGetCursorPos(window, &mouseX, &mouseY);

			// Render FPS counter (top-left)
			string fpsText = "FPS: " + to_string((int)fps);
			f.RenderText(fpsText, 10, 30, 0.4f, { 1.0f, 1.0f, 0.0f });

			// Render mouse position (below FPS)
			string mousePosText = "Mouse Pos : " + to_string(mouseX) + " " + to_string(mouseY);
			f.RenderText(mousePosText, 10, 50, 0.4f, { 1.0f, 1.0f, 0.0f });

			// Render mouse button states
			string leftButtonText = "Left Button: " + string(MouseController::LeftButtonClicked ? "Down" : "Up");
			f.RenderText(leftButtonText, 10, 70, 0.4f, { 1.0f, 1.0f, 0.0f });

			string middleButtonText = "Middle Button: " + string(MouseController::MiddleButtonClicked ? "Down" : "Up");
			f.RenderText(middleButtonText, 10, 90, 0.4f, { 1.0f, 1.0f, 0.0f });
		}

		// Render object info based on mode
		if (currentMode == 0)
		{
			// Mode 0: Fighter
			glm::vec3 fighterPos = m_fighterMode1.GetPosition();
			string fighterPosText = "Fighter Position: {vec3(" + to_string(fighterPos.x) + ", " + to_string(fighterPos.y) + ", " + to_string(fighterPos.z) + ")}";
			f.RenderText(fighterPosText, 10, 110, 0.4f, { 1.0f, 1.0f, 0.0f });

			glm::vec3 fighterRot = m_fighterMode1.GetRotation();
			string fighterRotText = "Fighter Rotation: {vec3(" + to_string(fighterRot.x) + ", " + to_string(fighterRot.y) + ", " + to_string(fighterRot.z) + ")}";
			f.RenderText(fighterRotText, 10, 130, 0.4f, { 1.0f, 1.0f, 0.0f });

			glm::vec3 fighterScale = m_fighterMode1.GetScale();
			string fighterScaleText = "Fighter Scale : {vec3(" + to_string(fighterScale.x) + ", " + to_string(fighterScale.y) + ", " + to_string(fighterScale.z) + ")}";
			f.RenderText(fighterScaleText, 10, 150, 0.4f, { 1.0f, 1.0f, 0.0f });
		}
		else if (currentMode == 1)
		{
			// Mode 1: Fighter (Transform)
			glm::vec3 fighterPos = m_fighterMode2.GetPosition();
			string fighterPosText = "Fighter Position: {vec3(" + to_string(fighterPos.x) + ", " + to_string(fighterPos.y) + ", " + to_string(fighterPos.z) + ")}";
			f.RenderText(fighterPosText, 10, 110, 0.4f, { 1.0f, 1.0f, 0.0f });

			glm::vec3 fighterRot = m_fighterMode2.GetRotation();
			string fighterRotText = "Fighter Rotation: {vec3(" + to_string(fighterRot.x) + ", " + to_string(fighterRot.y) + ", " + to_string(fighterRot.z) + ")}";
			f.RenderText(fighterRotText, 10, 130, 0.4f, { 1.0f, 1.0f, 0.0f });

			glm::vec3 fighterScale = m_fighterMode2.GetScale();
			string fighterScaleText = "Fighter Scale : {vec3(" + to_string(fighterScale.x) + ", " + to_string(fighterScale.y) + ", " + to_string(fighterScale.z) + ")}";
			f.RenderText(fighterScaleText, 10, 150, 0.4f, { 1.0f, 1.0f, 0.0f });
		}
		else if (currentMode == 3)
		{
			// Mode 3: Space Scene - Fighter info
			glm::vec3 fighterPos = m_spaceFighter.GetPosition();
			string fighterPosText = "Fighter Position: {vec3(" + to_string(fighterPos.x) + ", " + to_string(fighterPos.y) + ", " + to_string(fighterPos.z) + ")}";
			f.RenderText(fighterPosText, 10, 110, 0.4f, { 1.0f, 1.0f, 0.0f });

			glm::vec3 fighterRot = m_spaceFighter.GetRotation();
			string fighterRotText = "Fighter Rotation: {vec3(" + to_string(fighterRot.x) + ", " + to_string(fighterRot.y) + ", " + to_string(fighterRot.z) + ")}";
			f.RenderText(fighterRotText, 10, 130, 0.4f, { 1.0f, 1.0f, 0.0f });

			glm::vec3 fighterScale = m_spaceFighter.GetScale();
			string fighterScaleText = "Fighter Scale : {vec3(" + to_string(fighterScale.x) + ", " + to_string(fighterScale.y) + ", " + to_string(fighterScale.z) + ")}";
			f.RenderText(fighterScaleText, 10, 150, 0.4f, { 1.0f, 1.0f, 0.0f });
		}

		glfwSwapBuffers(WindowController::GetInstance().GetWindow());
		glfwPollEvents();
	} while (glfwGetKey(WindowController::GetInstance().GetWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(WindowController::GetInstance().GetWindow()) == 0);

	// Cleanup
	m_lightSphere.Cleanup();
	m_fighterMode1.Cleanup();
	m_fighterMode2.Cleanup();
	m_waterPlane.Cleanup();
	m_postProcessor.Cleanup();
	m_skybox.Cleanup();
	m_spaceFighter.Cleanup();
	m_asteroids.Cleanup();
	m_shaderColor.Cleanup();
	m_shaderDiffuse.Cleanup();
	m_shaderPosition.Cleanup();
	m_shaderFont.Cleanup();
	m_shaderPost.Cleanup();
	m_shaderSkybox.Cleanup();
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
	m_fighterMode1.SetSpecularStrength(specularStrength);
	m_fighterMode1.SetSpecularColor(specularColor);
	m_fighterMode1.SetCameraPosition(m_camera.GetPosition());

	// Render light sphere (white, unlit)
	m_lightSphere.Render(projectionView);

	// Render teapot with lighting
	m_fighterMode1.Render(projectionView);
}

// Mode 1: Transform - Update
void GameController::UpdateMode2()
{
	int currentMode = OpenGL::ToolWindow::CurrentMode;

	// DETECT MODE ENTRY: Reset transform when entering Mode 1
	if (m_previousMode != currentMode && currentMode == 1)
	{
		m_transformPosition = m_initialTransformPosition;
		m_transformRotation = m_initialTransformRotation;
		m_transformScale = m_initialTransformScale;
		m_fighterMode2.SetPosition(m_transformPosition);
		m_fighterMode2.SetRotation(m_transformRotation);
		m_fighterMode2.SetScale(m_transformScale);
		m_fighterMode2.SetRotationEnabled(false);  // Disable automatic rotation
	}
	m_previousMode = currentMode;

	// Handle manual reset button
	if (OpenGL::ToolWindow::ResetTransform)
	{
		m_transformPosition = m_initialTransformPosition;
		m_transformRotation = m_initialTransformRotation;
		m_transformScale = m_initialTransformScale;
		m_fighterMode2.SetPosition(m_transformPosition);
		m_fighterMode2.SetRotation(m_transformRotation);
		m_fighterMode2.SetScale(m_transformScale);
		OpenGL::ToolWindow::ResetTransform = false;
	}

	// Get mouse state
	glm::vec2 mouseDelta = MouseController::MouseDelta;

	// LEFT MOUSE BUTTON: XY Manipulation
	if (MouseController::LeftButtonClicked)
	{
		// Translation XY - Quadrant-based movement like light sphere (slightly faster)
		if (OpenGL::ToolWindow::EnableTranslate)
		{
			glm::vec2 direction = MouseController::MovementDirection;
			float speed = MouseController::MovementSpeed;

			// Move in XY plane using quadrant-based direction and speed
			// Light sphere uses 0.05f, this uses 0.06f to be slightly faster
			m_transformPosition.x += direction.x * speed * 0.06f;
			m_transformPosition.y += direction.y * speed * 0.06f;
			m_fighterMode2.SetPosition(m_transformPosition);
		}

		// Rotation XY: Rotate continuously based on mouse position (like translation movement)
		if (OpenGL::ToolWindow::EnableRotate)
		{
			glm::vec2 mousePos = MouseController::GetNormalizedPosition();
			const float rotateSensitivity = 0.02f;

			// Rotate based on mouse position - continuous rotation towards mouse
			m_transformRotation.x += mousePos.y * rotateSensitivity;
			m_transformRotation.y += mousePos.x * rotateSensitivity;

			m_fighterMode2.SetRotation(m_transformRotation);
		}

		// Scale XY - Non-uniform scaling based on mouse XY position
		if (OpenGL::ToolWindow::EnableScale)
		{
			glm::vec2 mousePos = MouseController::GetNormalizedPosition();
			const float scaleSensitivity = 0.0001f;

			// X mouse position affects X scale, Y mouse position affects Y scale
			m_transformScale.x += mousePos.x * scaleSensitivity;
			m_transformScale.y += mousePos.y * scaleSensitivity;

			// Clamp scale to safe range
			m_transformScale = glm::max(m_transformScale, glm::vec3(0.001f, 0.001f, 0.001f));
			m_transformScale = glm::min(m_transformScale, glm::vec3(2.0f, 2.0f, 2.0f));

			m_fighterMode2.SetScale(m_transformScale);
		}
	}

	// MIDDLE MOUSE BUTTON: Z-Axis Manipulation (based on Y mouse position)
	if (MouseController::MiddleButtonClicked)
	{
		glm::vec2 mousePos = MouseController::GetNormalizedPosition();

		// Translation Z - based on Y mouse position (continuous)
		if (OpenGL::ToolWindow::EnableTranslate)
		{
			const float translateZSensitivity = 0.02f;
			m_transformPosition.z += mousePos.y * translateZSensitivity;
			m_fighterMode2.SetPosition(m_transformPosition);
		}

		// Rotation Z - based on Y mouse position (continuous)
		if (OpenGL::ToolWindow::EnableRotate)
		{
			const float rotateZSensitivity = 0.02f;
			m_transformRotation.z += mousePos.y * rotateZSensitivity;
			m_fighterMode2.SetRotation(m_transformRotation);
		}

		// Scale Z - based on Y mouse position (continuous)
		if (OpenGL::ToolWindow::EnableScale)
		{
			const float scaleZSensitivity = 0.0001f;
			m_transformScale.z += mousePos.y * scaleZSensitivity;

			m_transformScale = glm::max(m_transformScale, glm::vec3(0.001f, 0.001f, 0.001f));
			m_transformScale = glm::min(m_transformScale, glm::vec3(2.0f, 2.0f, 2.0f));

			m_fighterMode2.SetScale(m_transformScale);
		}
	}

	// REMOVED: Automatic rotation (if (EnableRotate) { m_transformRotation.y += 0.01f; })
}

// Mode 1: Transform - Render
void GameController::RenderMode2()
{
	glm::mat4 projectionView = m_camera.GetProjection() * m_camera.GetView();

	// Set up lighting (reuse light position from Mode 0)
	m_lightSphere.SetPosition(m_lightPosition);
	m_lightSphere.SetScale(glm::vec3(0.05f, 0.05f, 0.05f));
	m_lightSphere.SetColor(glm::vec3(1.0f, 1.0f, 1.0f));

	Mesh::Lights.clear();
	Mesh::Lights.push_back(m_lightSphere);

	m_fighterMode2.SetCameraPosition(m_camera.GetPosition());

	// Render fighter only (lighting is enabled but sphere is not rendered)
	m_fighterMode2.Render(projectionView);
}

// Mode 2: Water Scene - Update
void GameController::UpdateMode3()
{
	// Get water parameters from UI
	float frequency = OpenGL::ToolWindow::WaterFrequency / 100.0f;  // 0.00-4.00
	float amplitude = OpenGL::ToolWindow::WaterAmplitude / 100.0f;  // 0.00-1.00
	bool wireframe = OpenGL::ToolWindow::WireframeRender;
	bool tintBlue = OpenGL::ToolWindow::TintBlue;

	// Apply wireframe mode
	if (wireframe)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	// Water parameters can be used for shader uniforms or animations in the future
	// For now, we'll just render the water plane as a simple mesh
}

// Mode 2: Water Scene - Render
void GameController::RenderMode3(Fonts* f, double fps)
{
	// Start post-processing (render to framebuffer)
	m_postProcessor.Start();

	glm::mat4 projectionView = m_camera.GetProjection() * m_camera.GetView();

	// Set up lighting (reuse light position from Mode 0)
	m_lightSphere.SetPosition(m_lightPosition);
	m_lightSphere.SetScale(glm::vec3(0.05f, 0.05f, 0.05f));
	m_lightSphere.SetColor(glm::vec3(1.0f, 1.0f, 1.0f));

	Mesh::Lights.clear();
	Mesh::Lights.push_back(m_lightSphere);

	// Apply tint color
	if (OpenGL::ToolWindow::TintBlue)
	{
		m_waterPlane.SetColor(glm::vec3(0.2f, 0.4f, 1.0f));  // Blue tint
	}
	else
	{
		m_waterPlane.SetColor(glm::vec3(1.0f, 1.0f, 1.0f));  // No tint
	}

	m_waterPlane.SetCameraPosition(m_camera.GetPosition());
	m_waterPlane.SetLightPosition(m_lightPosition);
	m_waterPlane.SetLightColor(glm::vec3(1.0f, 1.0f, 1.0f));

	// Render water plane only (lighting is enabled but sphere is not rendered)
	m_waterPlane.Render(projectionView);

	// Render text INSIDE the framebuffer so it gets post-processed
	// Get mouse position
	GLFWwindow* window = WindowController::GetInstance().GetWindow();
	double mouseX, mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);

	// Render FPS counter
	string fpsText = "FPS: " + to_string((int)fps);
	f->RenderText(fpsText, 10, 30, 0.4f, { 1.0f, 1.0f, 0.0f });

	// Render mouse position
	string mousePosText = "Mouse Pos : " + to_string(mouseX) + " " + to_string(mouseY);
	f->RenderText(mousePosText, 10, 50, 0.4f, { 1.0f, 1.0f, 0.0f });

	// Render mouse button states
	string leftButtonText = "Left Button: " + string(MouseController::LeftButtonClicked ? "Down" : "Up");
	f->RenderText(leftButtonText, 10, 70, 0.4f, { 1.0f, 1.0f, 0.0f });

	string middleButtonText = "Middle Button: " + string(MouseController::MiddleButtonClicked ? "Down" : "Up");
	f->RenderText(middleButtonText, 10, 90, 0.4f, { 1.0f, 1.0f, 0.0f });

	// Render fish info
	glm::vec3 fishPos = m_waterPlane.GetPosition();
	string fishPosText = "Fish Position: {vec3(" + to_string(fishPos.x) + ", " + to_string(fishPos.y) + ", " + to_string(fishPos.z) + ")}";
	f->RenderText(fishPosText, 10, 110, 0.4f, { 1.0f, 1.0f, 0.0f });

	glm::vec3 fishRot = m_waterPlane.GetRotation();
	string fishRotText = "Fish Rotation: {vec3(" + to_string(fishRot.x) + ", " + to_string(fishRot.y) + ", " + to_string(fishRot.z) + ")}";
	f->RenderText(fishRotText, 10, 130, 0.4f, { 1.0f, 1.0f, 0.0f });

	glm::vec3 fishScale = m_waterPlane.GetScale();
	string fishScaleText = "Fish Scale : {vec3(" + to_string(fishScale.x) + ", " + to_string(fishScale.y) + ", " + to_string(fishScale.z) + ")}";
	f->RenderText(fishScaleText, 10, 150, 0.4f, { 1.0f, 1.0f, 0.0f });

	// Manual post-processing with custom uniforms
	static float time = 0.0f;
	time += 0.01f;  // Increment time for animation

	// Switch to screen framebuffer and activate post-processing shader
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_DEPTH_TEST);
	glUseProgram(m_shaderPost.GetProgramID());

	// Set all shader uniforms
	m_shaderPost.SetTextureSampler("ScreenTexture", GL_TEXTURE0, 0, m_postProcessor.GetTextureID());
	m_shaderPost.SetFloat("Time", time);
	m_shaderPost.SetFloat("Frequency", (float)OpenGL::ToolWindow::WaterFrequency * 0.05f);  // Max: 400 * 0.05 = 20 (fewer, smoother waves)
	m_shaderPost.SetFloat("Amplitude", (float)OpenGL::ToolWindow::WaterAmplitude * 0.002f);  // Max: 100 * 0.002 = 0.2 (20% screen displacement)
	m_shaderPost.SetInt("TintBlue", OpenGL::ToolWindow::TintBlue ? 1 : 0);

	// Bind vertices and render the post-processed quad
	glBindBuffer(GL_ARRAY_BUFFER, m_postProcessor.GetVertexBuffer());
	glEnableVertexAttribArray(m_shaderPost.GetAttrVertices());
	glVertexAttribPointer(m_shaderPost.GetAttrVertices(), 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(m_shaderPost.GetAttrTexCoords());
	glVertexAttribPointer(m_shaderPost.GetAttrTexCoords(), 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(m_shaderPost.GetAttrVertices());
	glDisableVertexAttribArray(m_shaderPost.GetAttrTexCoords());
}

// Mode 3: Space Scene - Update
void GameController::UpdateMode4()
{
	// Save original camera view on first entry to this mode
	if (!m_cameraViewSaved)
	{
		m_originalCameraView = m_camera.GetView();
		m_originalCameraPosition = m_camera.GetPosition();
		m_cameraViewSaved = true;
	}

	// Generate random transformations for asteroids on first call
	static bool initialized = false;
	if (!initialized)
	{
		// Seed random with time (already done in Initialize())
		m_asteroidTransforms.clear();
		for (int i = 0; i < 100; i++)
		{
			AsteroidTransform transform;

			// Random position within larger range (-15 to 15 on each axis for more spread)
			transform.position.x = ((rand() % 3000) / 100.0f - 15.0f);
			transform.position.y = ((rand() % 3000) / 100.0f - 15.0f);
			transform.position.z = ((rand() % 3000) / 100.0f - 15.0f);

			// Random rotation (0-360 degrees on each axis)
			transform.rotation.x = (rand() % 360) * 1.0f;
			transform.rotation.y = (rand() % 360) * 1.0f;
			transform.rotation.z = (rand() % 360) * 1.0f;

			// Random scale (0.01 to 0.05)
			float scaleValue = 0.01f + (rand() % 40) / 1000.0f;
			transform.scale = glm::vec3(scaleValue, scaleValue, scaleValue);

			m_asteroidTransforms.push_back(transform);
		}
		initialized = true;
	}

	// Rotate camera in place (rotate view direction, not position)
	// Using the same approach as Lab6_DepthBlendCubeMaps
	static float cameraAngle = 0.0f;
	cameraAngle += 0.3f; // Rotation speed in degrees

	// Camera stays at original position
	glm::vec3 cameraPos = m_originalCameraPosition;

	// Rotate the look-at target around the camera (using degrees like Lab6)
	glm::vec3 lookAt;
	lookAt.x = cos(glm::radians(cameraAngle)) * 100.0f;
	lookAt.y = 0.0f;
	lookAt.z = sin(glm::radians(cameraAngle)) * 100.0f;

	glm::vec3 upVector = glm::vec3(0.0f, 1.0f, 0.0f);

	m_camera.SetView(glm::lookAt(cameraPos, lookAt, upVector));
}

// Mode 3: Space Scene - Render
void GameController::RenderMode4()
{
	glm::mat4 projectionView = m_camera.GetProjection() * m_camera.GetView();

	// Render skybox (remove translation from view matrix)
	glm::mat4 view = glm::mat4(glm::mat3(m_camera.GetView()));
	m_skybox.Render(m_camera.GetProjection() * view);

	// Set up lighting (reuse light from other modes)
	m_lightSphere.SetPosition(m_lightPosition);
	Mesh::Lights.clear();
	Mesh::Lights.push_back(m_lightSphere);

	// Render fighter (stationary at origin)
	m_spaceFighter.SetCameraPosition(m_camera.GetPosition());
	m_spaceFighter.Render(projectionView);

	// Render asteroids individually with different transforms
	m_asteroids.SetCameraPosition(m_camera.GetPosition());
	for (const auto& transform : m_asteroidTransforms)
	{
		m_asteroids.SetPosition(transform.position);
		m_asteroids.SetRotation(transform.rotation);
		m_asteroids.SetScale(transform.scale);
		m_asteroids.CalculateTransform();
		m_asteroids.Render(projectionView);
	}
}
