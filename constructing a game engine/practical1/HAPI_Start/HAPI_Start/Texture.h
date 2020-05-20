#pragma once

#include <HAPI_lib.h>
#include "Window.h"
#include "Rectangle.h"

class Texture
{
private:
	//texture filepath
	std::string m_Filepath;

	//texture size
	int m_TextureWidth{ 64 }, m_TextureHeight{64};

	int m_NumberOfFramesX, m_NumberOfFramesY, m_FrameWidth, m_FrameHeight;

	//texture memory
	HAPISPACE::BYTE *texture{ nullptr };

	//texture loaded
	bool textureLoaded = false;
private:
	//render by pixel if by line is not possible
	void renderTextureByPixel(const int &windowWidth, const int &windowHeight, const int &x, const int &y, const int frameNumber = 1);
public:
	//constructer
	Texture(const std::string &filepath, int numberOfFramesX = 1, int numberOfFramesY = 1);

	//function to load the texture
	bool loadTexture();

	//getters for width and height of the texture
	int getWidth() const;
	int getHeight() const;
	
	int getFrameNumber() const { return m_NumberOfFramesX * m_NumberOfFramesY; }

	// render functions without and with alpha value
	void renderTexture(const int &windowWidth, const int &windowHeight, const int &x, const int &y, const int frameNumber = 1);
	void renderTextureWithAlpha(const int &windowWidth, const int &windowHeight, const int &x, const int &y, const int frameNumber = 1);
	//HAPISPACE::BYTE* getPointer() const;
	~Texture();
};

