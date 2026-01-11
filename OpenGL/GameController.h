#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "standardincludes.h"
#include "Shader.h"
#include "Mesh.h"
#include "WindowController.h"
#include "Camera.h"
#include "PostProcessor.h"
#include "Skybox.h"

// Forward declaration
class Fonts;

class GameController : public Singleton<GameController>
{
public:
	// ctors
	GameController();
	virtual ~GameController() {}

	// Methods
	void Initialize();
	void RunGame();

private:
	// Shaders
	Shader m_shaderColor;
	Shader m_shaderDiffuse;
	Shader m_shaderPosition;
	Shader m_shaderFont;
	Shader m_shaderPost;
	Shader m_shaderSkybox;

	// Camera
	Camera m_camera;

	// Mode 0: Move Light
	Mesh m_lightSphere;
	Mesh m_fighterMode1;
	glm::vec3 m_lightPosition;

	// Mode 1: Transform
	Mesh m_fighterMode2;
	glm::vec3 m_transformPosition;
	glm::vec3 m_transformRotation;
	glm::vec3 m_transformScale;
	int m_previousMode;
	glm::vec3 m_initialTransformPosition;
	glm::vec3 m_initialTransformRotation;
	glm::vec3 m_initialTransformScale;
	glm::vec3 m_rotationAtClick;
	glm::vec3 m_scaleAtClick;
	bool m_wasLeftButtonDown;
	bool m_wasMiddleButtonDown;

	// Mode 2: Water Scene
	Mesh m_waterPlane;
	PostProcessor m_postProcessor;

	// Mode 3: Space Scene
	Skybox m_skybox;
	Mesh m_spaceFighter;
	Mesh m_asteroids;
	struct AsteroidTransform {
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;
	};
	std::vector<AsteroidTransform> m_asteroidTransforms;
	glm::mat4 m_originalCameraView;
	glm::vec3 m_originalCameraPosition;
	bool m_cameraViewSaved;

	// Helper methods
	void RenderMode1();
	void RenderMode2();
	void RenderMode3(Fonts* f, double fps);
	void RenderMode4();
	void UpdateMode1();
	void UpdateMode2();
	void UpdateMode3();
	void UpdateMode4();

};
#endif // GAME_CONTROLLER_H
