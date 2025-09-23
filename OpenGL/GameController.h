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
	Shader m_shader;
	Camera m_camera;
	Mesh m_mesh;
};
#endif // GAME_CONTROLLER_H
