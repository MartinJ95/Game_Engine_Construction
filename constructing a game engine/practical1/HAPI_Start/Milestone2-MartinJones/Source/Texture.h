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

	//texture loaded
	bool textureLoaded = false;
public:
	//render by pixel if by line is not possible
	void renderTextureByPixel(Window &window, int x, int y);
public:
	//constructer
	Texture(std::string filepath,int width, int height);

	//function to load the texture
	bool loadTexture();

	//getters for width and height of the texture
	int getWidth() const;
	int getHeight() const;

	// render functions without and with alpha value
	void renderTexture(Window &window, int x, int y);
	void renderTextureWithAlpha(Window &window, int x, int y);
	//HAPISPACE::BYTE* getPointer() const;
	~Texture();
};

