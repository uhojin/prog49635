#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "standardincludes.h"
#include "Shader.h"
#include "Mesh.h"
#include "WindowController.h"
#include "Camera.h"


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

	// Camera
	Camera m_camera;

	// Mode 1: Move Light
	Mesh m_lightSphere;
	Mesh m_teapotMode1;
	glm::vec3 m_lightPosition;

	// Mode 2: Color By Position
	Mesh m_teapotMode2;
	glm::vec3 m_teapotPosition;

	// Mode 3: Move Cubes To Sphere
	Mesh m_sphereMode3;
	vector<Mesh> m_cubes;

	// Helper methods
	void RenderMode1();
	void RenderMode2();
	void RenderMode3();
	void UpdateMode1();
	void UpdateMode2();
	void UpdateMode3();

};
#endif // GAME_CONTROLLER_H
