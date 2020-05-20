#include "Texture.h"

//constructer
Texture::Texture(std::string filepath, int width, int height) : m_Filepath(filepath), m_TextureWidth(width), m_TextureHeight(height)
{
}

//function to load texture
bool Texture::loadTexture()
{
	if (HAPI.LoadTexture(m_Filepath, &texture, m_TextureWidth, m_TextureHeight))
	{
		textureLoaded = true;
		return true;
	}
	else
	{
		HAPI.UserMessage("missing texture: " + m_Filepath, "failed to load texture");
		texture = new HAPISPACE::BYTE[m_TextureWidth * 4];
		HAPISPACE::BYTE *texturepnter = texture;
		for (int i = 0; i < m_TextureWidth; i++)
		{
			*(HAPISPACE::HAPI_TColour*)texturepnter = HAPISPACE::HAPI_TColour::HORRID_PINK;
			texturepnter += 4;
		}
		return true;
	}
}

//getter functions for width and height of texture
int Texture::getWidth() const
{
	return m_TextureWidth;
}

int Texture::getHeight() const
{
	return m_TextureHeight;
}

//render functions
void Texture::renderTexture(Window &window, int x, int y)
{
	if (x >= 0 && y >= 0 && x + m_TextureWidth <= window.getWidth() && y + m_TextureHeight <= window.getHeight())
	{
		HAPISPACE::BYTE *screen = HAPI.GetScreenPointer();
		HAPISPACE::BYTE *screenPnter = screen + (x + y * window.getWidth()) * 4;
		HAPISPACE::BYTE *texturePnter = texture;
		for (int y = 0; y < m_TextureHeight; y++)
		{
			memcpy(screenPnter, texturePnter, m_TextureWidth * 4);
			if (textureLoaded)
			{
				texturePnter += m_TextureWidth * 4;
			}
			screenPnter += window.getWidth() * 4;
		}
	}
	else
	{
		renderTextureByPixel(window, x, y);
	}
}

void Texture::renderTextureByPixel(Window &window, int x, int y)
{
	HAPISPACE::BYTE *screen = HAPI.GetScreenPointer();
	HAPISPACE::BYTE *texturePnter = texture;
	//unsigned int offset = ((x + y * window.getWidth()) * 4);
	//HAPISPACE::BYTE *pnter = screen + offset;
	for (int gy = y; gy < y + m_TextureHeight; gy++)
	{
		for (int gx = x; gx < x + m_TextureHeight; gx++)
		{
			if (gx > 0 && gy > 0 && gx < window.getWidth() && gy < window.getHeight())
			{
				unsigned int offset = ((gx + gy * window.getWidth()) * 4);
				HAPISPACE::BYTE *pnter = screen + offset;
				if (!textureLoaded)
				{
					*(HAPISPACE::HAPI_TColour*)pnter = HAPISPACE::HAPI_TColour::HORRID_PINK;
				}
				else
				{
					*(HAPISPACE::HAPI_TColour*)pnter = *(HAPISPACE::HAPI_TColour*)texturePnter;
				}
			}
			if (textureLoaded)
			{
				texturePnter += 4;
			}
			//pnter += 4;
		}
		//pnter += (window.getWidth() - m_TextureWidth) * 4;
		//texturePnter += 4;
	}
}

void Texture::renderTextureWithAlpha(Window &window, int x, int y)
{
	HAPISPACE::BYTE *screen = HAPI.GetScreenPointer();
	HAPISPACE::BYTE *texturePnter = texture;
	//unsigned int offset = ((x + y * window.getWidth()) * 4);
	//HAPISPACE::BYTE *pnter = screen + offset;
	for (int gy = y; gy < y + m_TextureHeight; gy++)
	{
		for (int gx = x; gx < x + m_TextureWidth; gx++)
		{
			if (gx > 0 && gy > 0 && gx < window.getWidth() && gy < window.getHeight())
			{
				if (texturePnter[3] == 0)
				{
					
				}
				else if (texturePnter[3] == 255)
				{
					unsigned int offset = ((gx + gy * window.getWidth()) * 4);
					HAPISPACE::BYTE *pnter = screen + offset;
					*(HAPISPACE::HAPI_TColour*)pnter = *(HAPISPACE::HAPI_TColour*)texturePnter;
				}
				else
				{
					unsigned int offset = ((gx + gy * window.getWidth()) * 4);
					HAPISPACE::BYTE *pnter = screen + offset;
					HAPISPACE::BYTE red = texturePnter[0];
					HAPISPACE::BYTE green = texturePnter[1];
					HAPISPACE::BYTE blue = texturePnter[2];
					HAPISPACE::BYTE alpha = texturePnter[3];
					float mod = alpha / 255.0f;
					pnter[0] = pnter[0] + ((alpha*(blue - pnter[0])) >> 8);
					pnter[1] = pnter[1] + ((alpha*(green - pnter[1])) >> 8);
					pnter[2] = pnter[2] + ((alpha*(red - pnter[2])) >> 8);
				}


			}
			if (textureLoaded)
			{
				texturePnter += 4;
			}
			//pnter += 4;
		}
		//texturePnter += 4;
		//pnter += (window.getWidth() - m_TextureWidth) * 4;
	}
}

Texture::~Texture()
{
	delete[] texture;
}
