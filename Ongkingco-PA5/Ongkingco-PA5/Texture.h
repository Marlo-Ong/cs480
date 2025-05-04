#pragma once
#include "graphics_headers.h"
#include <SOIL2/SOIL2.h>

class Texture
{

public:
	Texture();
	Texture(const char* fileName);
	bool loadTexture(const char* texFile);
	GLuint getTextureID() { return m_TextureID; }

private:
	GLuint m_TextureID;

	bool initializeTexture();

};

