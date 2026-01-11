#ifndef MESH_H
#define MESH_H

#include "standardincludes.h"
#include "Texture.h"

// Forward declarations for OBJ_Loader types
namespace objl
{
	struct Vector3;
	struct Vertex;
}

class Shader;
class Mesh
{
public:
	// ctors
	Mesh();
	virtual ~Mesh();

	// Accessors
	void SetPosition(glm::vec3 _position) { m_position = _position; }
	glm::vec3 GetPosition() { return m_position; }
	void SetRotation(glm::vec3 _rotation) { m_rotation = _rotation; }
	glm::vec3 GetRotation() { return m_rotation; }
	void SetScale(glm::vec3 _scale) { m_scale = _scale; }
	glm::vec3 GetScale() { return m_scale; }
	void SetColor(glm::vec3 _color) { m_color = _color; }
	glm::vec3 GetColor() { return m_color; }
	void SetLightPosition(glm::vec3 _lightPosition) { m_lightPosition = _lightPosition; }
	void SetLightColor(glm::vec3 _lightColor) { m_lightColor = _lightColor; }
	void SetCameraPosition(glm::vec3 _cameraPosition) { m_cameraPosition = _cameraPosition; }
	void SetSpecularStrength(float _strength) { m_specularStrength = _strength; }
	void SetSpecularColor(glm::vec3 _specColor) { m_specularColor = _specColor; }
	void SetRotationEnabled(bool _enabled) { m_rotationEnabled = _enabled; }
	// Methods
	void Create(Shader* _shader, string _file);
	void CreateFromVertexData(Shader* _shader, const vector<GLfloat>& _vertexData, const string& _texturePath);
	void Cleanup();
	void CalculateTransform();
	void Render(glm::mat4 _pv);

	// Members
	static vector<Mesh> Lights;

private:
	// Methods
	void SetShaderVariables(glm::mat4 _pv);
	void BindAttributes();
	string Concat(string _s1, int _index, string _s2);
	void CalculateTangents(vector<objl::Vertex> _vertices, objl::Vector3& _tangent, objl::Vector3& _bitangent);
	string RemoveFolder(string _map);

	// Members
	Shader* m_shader;
	Texture m_textureDiffuse;
	Texture m_textureSpecular;
	Texture m_textureNormal;
	GLuint m_vertexBuffer;
	GLuint m_indexBuffer;
	std::vector<GLfloat> m_vertexData;
	std::vector<GLubyte> m_indexData;
	bool m_enableNormalMap;
	int m_elementSize;


	// Transform
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;
	glm::mat4 m_world;
	glm::vec3 m_cameraPosition;
	glm::vec3 m_color;

	// Lights
	glm::vec3 m_lightPosition;
	glm::vec3 m_lightColor;

	// Material properties
	float m_specularStrength;
	glm::vec3 m_specularColor;

	// Rotation control
	bool m_rotationEnabled;
};
#endif // !MESH_H
