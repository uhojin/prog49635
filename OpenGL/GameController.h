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
	Shader m_shaderColor;
	Shader m_shaderDiffuse;
	Shader m_shaderFont;
	Camera m_camera;
	vector<Mesh> m_meshBoxes;

};
#endif // GAME_CONTROLLER_H
