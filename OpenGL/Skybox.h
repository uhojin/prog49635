#ifndef SKYBOX_H
#define SKYBOX_H

#include "Mesh.h"

class Skybox
{
public:
	// ctors
	Skybox();
	virtual ~Skybox();

	// Methods
	void Create(Shader* _shader, string _file, vector<string> _faces);
	void Cleanup();
	void Render(glm::mat4 _pv);

private:
	// methods
	void SetShaderVariables(glm::mat4 _pv);
	void BindAttributes();

	// members
	Shader* m_shader;
	Texture m_texture;
	GLuint m_vertexBuffer; // GPU buffer
	std::vector<GLfloat> m_vertexData; // data in RAM
};

#endif // SKYBOX_H
