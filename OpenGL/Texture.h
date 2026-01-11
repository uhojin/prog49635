#ifndef TEXTURE_H
#define TEXTURE_H

#include "standardincludes.h"

class Texture
{
	public:
	Texture();
	virtual ~Texture() { }

	// Accessors
	GLuint GetTexture() { return m_texture; }

	// Methods
	void LoadTexture(string _fileName);
	void LoadCubemap(vector<std::string> _faces);
	void Cleanup();

private:
	//members
	int m_width;
	int m_height;
	int m_channels;
	GLuint m_texture;

	// Methods
	bool EndsWith(const std::string& str, const std::string& _suffix);
};

#endif // TEXTURE_H