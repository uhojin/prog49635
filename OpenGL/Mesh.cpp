#include "Mesh.h"
#include "Shader.h"

Mesh::Mesh()
{
	m_shader = nullptr;
	m_texture = { };
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_position = { 0, 0, 0 };
	m_rotation = { 0, 0, 0 };
}

Mesh::~Mesh()
{

}

void Mesh::Create(Shader* _shader)
{
	m_shader = _shader;
	m_texture = Texture();
	m_texture.LoadTexture("../Assets/Textures/Wood.jpg");

	m_vertexData = {
		//  X     Y     Z       R     G     B        S     T
		50.0f, 50.0f, 0.0f,   1.0f, 0.0f, 0.0f,		1.0f, 1.0f,		// Top Right
		50.0f, -50.0f, 0.0f,  0.0f, 1.0f, 0.0f,		1.0f, 0.0f,		// Bottom Right
		-50.0f, -50.0f, 0.0f, 0.0f, 0.0f, 1.0f,		0.0f, 0.0f,		// Bottom Left
		-50.0f, 50.0f, 0.0f,  1.0f, 1.0f, 1.0f,		0.0f, 1.0f		// Top Left
	};

	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_vertexData.size() * sizeof(GLfloat), m_vertexData.data(), GL_STATIC_DRAW);

	m_indexData = {
		2, 0, 3, 2, 1, 0
	};

	glGenBuffers(1, &m_indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexData.size() * sizeof(GLubyte), m_indexData.data(), GL_STATIC_DRAW);
}

void Mesh::Cleanup()
{
	glDeleteBuffers(1, &m_indexBuffer);
	glDeleteBuffers(1, &m_vertexBuffer);
	m_texture.Cleanup();
}

void Mesh::Render(glm::mat4 _wvp)
{
	glUseProgram(m_shader->GetProgramID()); // Use our own shader

	// 1st attr buffer : vertices
	glEnableVertexAttribArray(m_shader->GetAttrVertices());
	glVertexAttribPointer(
		m_shader->GetAttrVertices(),	// Attribute we want to configure
		3,								// size 
		GL_FLOAT,						// type
		GL_FALSE,						// normalized?
		8 * sizeof(float),				// stride (8 floats per vertex definition)
		(void*)0						// array buffer offset
	);

	// 2nd attribute buffer : colors
	glEnableVertexAttribArray(m_shader->GetAttrColors());
	glVertexAttribPointer(m_shader->GetAttrColors(),	// The Attribute we want to configure
		4,												// size (4 components per color value)
		GL_FLOAT,										// type
		GL_FALSE,										// normalized?
		8 * sizeof(float),								// stride (8 floats per vertex definition)
		(void*)(3 * sizeof(float))						// array buffer offset
	);

	// 3rd attribute : texCoords
	glEnableVertexAttribArray(m_shader->GetAttrTexCoords());
	glVertexAttribPointer(m_shader->GetAttrTexCoords(), // The Attribute we want to configure
		2,												// size (2 components per texCoord value)
		GL_FLOAT,										// type
		GL_FALSE,										// normalized?
		8 * sizeof(float),								// stride (8 floats per vertex definition)
		(void*)(6 * sizeof(float))						// array buffer offset
	);

	// 4th attribute : WVP
	m_rotation.y += 0.005f;
	glm::mat4 transform = glm::rotate(_wvp, m_rotation.y, glm::vec3(0, 1, 0));
	glUniformMatrix4fv(m_shader->GetAttrWVP(), 1, GL_FALSE, &transform[0][0]);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture.GetTexture());
	glUniform1i(m_shader->GetSampler1(), 0);

	
	glDrawElements(
		GL_TRIANGLES,				// mode
		m_indexData.size(),		// count
		GL_UNSIGNED_BYTE,			// type
		(void*)0					// element array buffer offset
	);
	
	glDisableVertexAttribArray(m_shader->GetAttrColors());
	glDisableVertexAttribArray(m_shader->GetAttrVertices());
	glDisableVertexAttribArray(m_shader->GetAttrTexCoords());
}