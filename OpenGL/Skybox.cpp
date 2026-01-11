#include "Skybox.h"
#include "Shader.h"

Skybox::Skybox()
{
	m_shader = nullptr;
	m_vertexBuffer = 0;
	m_texture = { };
}
Skybox::~Skybox()
{
}

void Skybox::Cleanup()
{
	glDeleteBuffers(1, &m_vertexBuffer);
	m_texture.Cleanup();
}

void Skybox::Create(Shader* _shader, string _file, vector<string> _faces)
{
	m_shader = _shader;

	// Hardcoded skybox cube vertices (instead of loading from OBJ file)
	// This avoids linker issues with OBJ_Loader being included in multiple files
	float skyboxVertices[] = {
		// positions
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
	};

	// Copy vertices to m_vertexData
	for (int i = 0; i < 108; i++)
	{
		m_vertexData.push_back(skyboxVertices[i]);
	}

	m_texture = Texture();
	m_texture.LoadCubemap(_faces);

	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_vertexData.size() * sizeof(float), m_vertexData.data(), GL_STATIC_DRAW);
}

void Skybox::SetShaderVariables(glm::mat4 _pv)
{
	m_shader->SetMat4("PV", _pv);
	m_shader->SetTextureSampler("skyboxTexture", GL_TEXTURE_CUBE_MAP, 0, m_texture.GetTexture());
}

void Skybox::BindAttributes()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);

	// attribute buffer : vertices
	glEnableVertexAttribArray(m_shader->GetAttrVertices());
	glVertexAttribPointer(m_shader->GetAttrVertices(),	// attribute
		3,								// size
		GL_FLOAT,						// type
		GL_FALSE,						// normalized?
		3 * sizeof(float),				// stride
		(void*)0						// array buffer offset
	);
}

void Skybox::Render(glm::mat4 _pv)
{
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);

	glUseProgram(m_shader->GetProgramID());
	SetShaderVariables(_pv);
	BindAttributes();

	glDrawArrays(GL_TRIANGLES, 0, m_vertexData.size());
	glDisableVertexAttribArray(m_shader->GetAttrNormals());

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
}
