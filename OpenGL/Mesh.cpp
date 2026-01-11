#include "Mesh.h"
#include "Shader.h"
#include "OBJ_Loader.h"



vector<Mesh> Mesh::Lights;

Mesh::Mesh()
{
	m_shader = nullptr;
	m_textureDiffuse = { };
	m_textureSpecular = { };
	m_textureNormal = { };
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_position = { 0, 0, 0 };
	m_rotation = { 0, 0, 0 };
	m_scale = { 1, 1, 1 };
	m_world = glm::mat4();
	m_specularStrength = 8.0f;
	m_specularColor = glm::vec3(1.0f, 1.0f, 1.0f);
	m_rotationEnabled = true;
	m_enableNormalMap = false;
	m_elementSize = 0;
}

Mesh::~Mesh()
{

}

void Mesh::Create(Shader* _shader, string _file)
{
	m_shader = _shader;

	objl::Loader Loader;
	M_ASSERT(Loader.LoadFile(_file) == true, "Failed to load mesh file"); // load obj file

	for (unsigned int i = 0; i < Loader.LoadedMeshes.size(); i++)
	{
		objl::Mesh curMesh = Loader.LoadedMeshes[i];
		vector<objl::Vector3> tangents;
		vector<objl::Vector3> bitangents;
		vector<objl::Vertex> triangle;
		objl::Vector3 tangent;
		objl::Vector3 bitangent;

		// Calculate tangents and bitangents per triangle
		for (unsigned int j = 0; j < curMesh.Vertices.size(); j += 3)
		{
			triangle.clear();
			triangle.push_back(curMesh.Vertices[j]);
			triangle.push_back(curMesh.Vertices[j + 1]);
			triangle.push_back(curMesh.Vertices[j + 2]);
			CalculateTangents(triangle, tangent, bitangent);
			tangents.push_back(tangent);
			bitangents.push_back(bitangent);
		}

		// Build vertex data with optional tangents/bitangents
		for (unsigned int j = 0; j < curMesh.Vertices.size(); j++)
		{
			// Position
			m_vertexData.push_back(curMesh.Vertices[j].Position.X);
			m_vertexData.push_back(curMesh.Vertices[j].Position.Y);
			m_vertexData.push_back(curMesh.Vertices[j].Position.Z);
			// Normal
			m_vertexData.push_back(curMesh.Vertices[j].Normal.X);
			m_vertexData.push_back(curMesh.Vertices[j].Normal.Y);
			m_vertexData.push_back(curMesh.Vertices[j].Normal.Z);
			// TexCoord
			m_vertexData.push_back(curMesh.Vertices[j].TextureCoordinate.X);
			m_vertexData.push_back(curMesh.Vertices[j].TextureCoordinate.Y);

			// Conditionally add tangent/bitangent if normal map exists
			if (Loader.LoadedMaterials[0].map_bump != "")
			{
				int index = j / 3;
				// Tangent
				m_vertexData.push_back(tangents[index].X);
				m_vertexData.push_back(tangents[index].Y);
				m_vertexData.push_back(tangents[index].Z);
				// Bitangent
				m_vertexData.push_back(bitangents[index].X);
				m_vertexData.push_back(bitangents[index].Y);
				m_vertexData.push_back(bitangents[index].Z);
			}
		}
	}

	// Load textures
	m_textureDiffuse = Texture();
	m_textureDiffuse.LoadTexture("../Assets/Textures/" + RemoveFolder(Loader.LoadedMaterials[0].map_Kd));

	m_textureSpecular = Texture();
	if (Loader.LoadedMaterials[0].map_Ks != "")
	{
		m_textureSpecular.LoadTexture("../Assets/Textures/" + RemoveFolder(Loader.LoadedMaterials[0].map_Ks));
	}

	m_textureNormal = Texture();
	if (Loader.LoadedMaterials[0].map_bump != "")
	{
		m_textureNormal.LoadTexture("../Assets/Textures/" + RemoveFolder(Loader.LoadedMaterials[0].map_bump));
		m_enableNormalMap = true;
	}

	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_vertexData.size() * sizeof(GLfloat), m_vertexData.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::CreateFromVertexData(Shader* _shader, const vector<GLfloat>& _vertexData, const string& _texturePath)
{
	m_shader = _shader;
	m_vertexData = _vertexData;

	// Load textures
	m_textureDiffuse = Texture();
	m_textureDiffuse.LoadTexture(_texturePath);
	m_textureSpecular = Texture();
	m_textureSpecular.LoadTexture(_texturePath);

	// Create vertex buffer
	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_vertexData.size() * sizeof(GLfloat), m_vertexData.data(), GL_STATIC_DRAW);
}

string Mesh::Concat(string _s1, int _index, string _s2)
{
	string index = to_string(_index);
	return _s1 + index + _s2;
}

string Mesh::RemoveFolder(string _map)
{
	const size_t last_slash_idx = _map.find_last_of("\\/");
	if (std::string::npos != last_slash_idx)
	{
		_map.erase(0, last_slash_idx + 1);
	}
	return _map;
}

void Mesh::CalculateTangents(vector<objl::Vertex> _vertices, objl::Vector3& _tangent, objl::Vector3& _bitangent)
{
	objl::Vector3 edge1 = _vertices[1].Position - _vertices[0].Position;
	objl::Vector3 edge2 = _vertices[2].Position - _vertices[0].Position;
	objl::Vector2 deltaUV1 = _vertices[1].TextureCoordinate - _vertices[0].TextureCoordinate;
	objl::Vector2 deltaUV2 = _vertices[2].TextureCoordinate - _vertices[0].TextureCoordinate;

	float f = 1.0f / (deltaUV1.X * deltaUV2.Y - deltaUV2.X * deltaUV1.Y);

	_tangent.X = f * (deltaUV2.Y * edge1.X - deltaUV1.Y * edge2.X);
	_tangent.Y = f * (deltaUV2.Y * edge1.Y - deltaUV1.Y * edge2.Y);
	_tangent.Z = f * (deltaUV2.Y * edge1.Z - deltaUV1.Y * edge2.Z);

	_bitangent.X = f * (-deltaUV2.X * edge1.X + deltaUV1.X * edge2.X);
	_bitangent.Y = f * (-deltaUV2.X * edge1.Y + deltaUV1.X * edge2.Y);
	_bitangent.Z = f * (-deltaUV2.X * edge1.Z + deltaUV1.X * edge2.Z);
}

void Mesh::Cleanup()
{
	glDeleteBuffers(1, &m_vertexBuffer);
	m_textureDiffuse.Cleanup();
	m_textureSpecular.Cleanup();
	m_textureNormal.Cleanup();
}

void Mesh::BindAttributes()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);

	int stride = m_enableNormalMap ? 14 * sizeof(float) : 8 * sizeof(float);

	// 1st attr buffer : vertices
	glEnableVertexAttribArray(m_shader->GetAttrVertices());
	glVertexAttribPointer(
		m_shader->GetAttrVertices(),	// Attribute we want to configure
		3,								// size
		GL_FLOAT,						// type
		GL_FALSE,						// normalized?
		stride,							// stride
		(void*)0						// array buffer offset
	);

	// 2nd attribute buffer : normals
	glEnableVertexAttribArray(m_shader->GetAttrNormals());
	glVertexAttribPointer(m_shader->GetAttrNormals(),	// The Attribute we want to configure
		3,												// size (3 components per normal value)
		GL_FLOAT,										// type
		GL_FALSE,										// normalized?
		stride,											// stride
		(void*)(3 * sizeof(float))						// array buffer offset
	);

	// 3rd attribute : texCoords
	glEnableVertexAttribArray(m_shader->GetAttrTexCoords());
	glVertexAttribPointer(m_shader->GetAttrTexCoords(), // The Attribute we want to configure
		2,												// size (2 components per texCoord value)
		GL_FLOAT,										// type
		GL_FALSE,										// normalized?
		stride,											// stride
		(void*)(6 * sizeof(float))						// array buffer offset
	);

	m_elementSize = 8;

	// 4th & 5th attributes : tangents and bitangents (only if normal map is enabled)
	if (m_enableNormalMap)
	{
		glEnableVertexAttribArray(m_shader->GetAttrTangents());
		glVertexAttribPointer(m_shader->GetAttrTangents(),
			3,
			GL_FLOAT,
			GL_FALSE,
			stride,
			(void*)(8 * sizeof(float))
		);

		glEnableVertexAttribArray(m_shader->GetAttrBitangents());
		glVertexAttribPointer(m_shader->GetAttrBitangents(),
			3,
			GL_FLOAT,
			GL_FALSE,
			stride,
			(void*)(11 * sizeof(float))
		);

		m_elementSize += 6;
	}
}

void Mesh::CalculateTransform()
{
	m_world = glm::translate(glm::mat4(1.0f), m_position);
	m_world = glm::rotate(m_world, m_rotation.x, glm::vec3(1, 0, 0));
	m_world = glm::rotate(m_world, m_rotation.y, glm::vec3(0, 1, 0));
	m_world = glm::rotate(m_world, m_rotation.z, glm::vec3(0, 0, 1));
	m_world = glm::scale(m_world, m_scale);
}

void Mesh::SetShaderVariables(glm::mat4 _pv)
{
	m_shader->SetMat4("World", m_world);
	m_shader->SetMat4("WVP", _pv * m_world);
	m_shader->SetVec3("CameraPosition", m_cameraPosition);
	m_shader->SetVec3("color", m_color);


	// Configure lights
	for (unsigned int i = 0; i < Lights.size(); i++)
	{
		m_shader->SetFloat(Concat("lights[", i, "].constant").c_str(), 1.0f);
		m_shader->SetFloat(Concat("lights[", i, "].linear").c_str(), 0.09f);
		m_shader->SetFloat(Concat("lights[", i, "].quadratic").c_str(), 0.032f);

		m_shader->SetVec3(Concat("lights[", i, "].ambientColor").c_str(), { 0.1f, 0.1f, 0.1f });
		m_shader->SetVec3(Concat("lights[", i, "].diffuseColor").c_str(), Lights[i].GetColor());
		m_shader->SetVec3(Concat("lights[", i, "].specularColor").c_str(), m_specularColor);

		m_shader->SetVec3(Concat("lights[", i, "].position").c_str(), Lights[i].GetPosition());
		m_shader->SetVec3(Concat("lights[", i, "].direction").c_str(), glm::normalize(glm::vec3({ 0.0f + i * 0.1f, 0, 0.0f + i * 0.1f }) - Lights[i].GetPosition()));
		m_shader->SetFloat(Concat("lights[", i, "].coneAngle").c_str(), glm::radians(5.0f));
		m_shader->SetFloat(Concat("lights[", i, "].falloff").c_str(), 200);
	}
	
	// Configure material
	m_shader->SetFloat("material.specularStrength", m_specularStrength);
	m_shader->SetTextureSampler("material.diffuseTexture", GL_TEXTURE0, 0, m_textureDiffuse.GetTexture());
	m_shader->SetTextureSampler("material.specularTexture", GL_TEXTURE1, 1, m_textureSpecular.GetTexture());
	m_shader->SetTextureSampler("material.normalTexture", GL_TEXTURE2, 2, m_textureNormal.GetTexture());
	m_shader->SetInt("EnableNormalMap", m_enableNormalMap);
}

void Mesh::Render(glm::mat4 _pv)
{
	glUseProgram(m_shader->GetProgramID()); // use our shader

	if (m_rotationEnabled)
	{
		m_rotation.x += 0.001f; // rotate around X axis each frame
	}

	CalculateTransform();
	SetShaderVariables(_pv);
	BindAttributes();

	glDrawArrays(GL_TRIANGLES, 0, m_vertexData.size());
	glDisableVertexAttribArray(m_shader->GetAttrNormals());
	glDisableVertexAttribArray(m_shader->GetAttrVertices());
	glDisableVertexAttribArray(m_shader->GetAttrTexCoords());
}