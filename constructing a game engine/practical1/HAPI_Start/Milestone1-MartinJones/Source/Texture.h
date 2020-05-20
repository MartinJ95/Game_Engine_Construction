#pragma once

#include <HAPI_lib.h>
#include "Window.h"

class Texture
{
private:
	//texture filepath
	std::string m_Filepath;

	//texture size
	int m_TextureWidth, m_TextureHeight;

	//texture memory
	HAPISPACE::BYTE *texture{ nullptr };
public:
	Texture(std::string filepath,int width, int height);
	bool loadTexture();
	int getWidth() const;
	int getHeight() const;
	void renderTexture(Window &window, int x, int y);
	void renderTextureWithAlpha(Window &window, int x, int y);
	//HAPISPACE::BYTE* getPointer() const;
	~Texture();
};

