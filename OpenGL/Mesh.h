#ifndef MESH_H
#define MESH_H

#include "standardincludes.h"
class Shader;
class Mesh
{
public:
	// ctors
	Mesh();
	virtual ~Mesh();

	// Methods
	void Create(Shader* _shader);
	void Cleanup();
	void Render();

private:
	Shader* m_shader;
	GLuint m_vertexBuffer;
	std::vector<GLfloat> m_vertexData;
};
#endif // !MESH_H
