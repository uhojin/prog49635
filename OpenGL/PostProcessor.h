#ifndef POSTPROCESSOR_H
#define POSTPROCESSOR_H

#include "..\OpenGL\standardincludes.h"
#include "Texture.h"

class Shader;

class PostProcessor
{
public:
	// ctors
	PostProcessor();
	virtual ~PostProcessor();

	// Methods
	void Create(Shader* _postShader);
	void Cleanup();
	void Start();
	void End();
	GLuint GetTextureID() const { return m_textureColorbuffer; }
	GLuint GetVertexBuffer() const { return m_vertexBuffer; }

private:
	// members
	GLuint m_framebuffer;
	GLuint m_textureColorbuffer;
	GLuint m_renderBufferObject;
	GLuint m_vertexBuffer; // GPU
	Shader* m_postShader;

	// Methods
	void CreateVertices();
	void CreateBuffers();
	void BindVertices();
};
#endif // POSTPROCESSOR_H