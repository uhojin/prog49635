#include "PostProcessor.h"
#include "WindowController.h"
#include "Shader.h"

PostProcessor::PostProcessor()
{
	m_framebuffer = 0;
	m_textureColorbuffer = 0;
	m_renderBufferObject = 0;
	m_vertexBuffer = 0;
	m_postShader = 0;
}

PostProcessor::~PostProcessor()
{
}

void PostProcessor::Cleanup()
{
	glDeleteFramebuffers(1, &m_framebuffer);
	glDeleteTextures(1, &m_textureColorbuffer);
	glDeleteRenderbuffers(1, &m_renderBufferObject);
}

void PostProcessor::Create(Shader* _postShader)
{
	m_postShader = _postShader;
	CreateVertices();
	CreateBuffers();
}

void PostProcessor::CreateBuffers()
{
	// framebuffer config
	glGenFramebuffers(1, &m_framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);

	// create a color attachment texture
	glGenTextures(1, &m_textureColorbuffer);
	glBindTexture(GL_TEXTURE_2D, m_textureColorbuffer);
	Resolution r = WindowController::GetInstance().GetResolution();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, r.m_width, r.m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);  // Repeat to create multiple fish
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_textureColorbuffer, 0);

	// create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
	glGenRenderbuffers(1, &m_renderBufferObject);
	glBindRenderbuffer(GL_RENDERBUFFER, m_renderBufferObject);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, r.m_width, r.m_height); // use a single renderbuffer object for both a depth AND stencil buffer.
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_renderBufferObject);

	// now that we actually created the framebuffer and added all attachments we want to check if it is complete
	M_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "ERROR::POSTPROCESSOR: Failed to initialize framebuffer.");
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
 }

void PostProcessor::CreateVertices()
{
	float vertexData[] = {
		// positions   // texCoords
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f
	};
	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void PostProcessor::BindVertices()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glEnableVertexAttribArray(m_postShader->GetAttrVertices());
	// 1st attribute buffer : vertices
	glVertexAttribPointer(m_postShader->GetAttrVertices(),
		2,
		GL_FLOAT,
		GL_FALSE,
		4 * sizeof(float),
		(void*)0);

	// 2nd attribute buffer : texCoords
	glEnableVertexAttribArray(m_postShader->GetAttrTexCoords());
	glVertexAttribPointer(m_postShader->GetAttrTexCoords(),
		2,
		GL_FLOAT,
		GL_FALSE,
		4 * sizeof(float),
		(void*)(2 * sizeof(float)));
}

void PostProcessor::Start()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
}

void PostProcessor::End()
{
	// This method is kept for backward compatibility
	// For custom shader uniforms, the calling code should manually handle the rendering
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_DEPTH_TEST);
	glUseProgram(m_postShader->GetProgramID());
	m_postShader->SetTextureSampler("ScreenTexture", GL_TEXTURE0, 0, m_textureColorbuffer);
	BindVertices();
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // wireframe mode
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(m_postShader->GetAttrVertices());
	glDisableVertexAttribArray(m_postShader->GetAttrTexCoords());
}