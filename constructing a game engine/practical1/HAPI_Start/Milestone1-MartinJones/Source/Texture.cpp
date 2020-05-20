#include "Texture.h"


Texture::Texture(std::string filepath, int width, int height) : m_Filepath(filepath), m_TextureWidth(width), m_TextureHeight(height)
{
}

bool Texture::loadTexture()
{
	if (HAPI.LoadTexture(m_Filepath, &texture, m_TextureWidth, m_TextureHeight))
	{
		return true;
	}
	else
	{
		return false;
	}
}

int Texture::getWidth() const
{
	return m_TextureWidth;
}

int Texture::getHeight() const
{
	return m_TextureHeight;
}

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
			texturePnter += m_TextureWidth * 4;
			screenPnter += window.getWidth() * 4;
		}
	}
	else
	{
		renderTextureWithAlpha(window, x, y);
	}
}

void Texture::renderTextureWithAlpha(Window &window, int x, int y)
{
	HAPISPACE::BYTE *screen = HAPI.GetScreenPointer();
	HAPISPACE::BYTE *texturePnter = texture;
	for (int gy = y; gy < y + m_TextureHeight; gy++)
	{
		for (int gx = x; gx < x + m_TextureHeight; gx++)
		{
			if (gx > 0 && gy > 0 && gx < window.getWidth() && gy < window.getHeight())
			{
				unsigned int offset = (gx + gy * window.getWidth());
				HAPISPACE::BYTE *pnter = screen + offset;
				pnter[0] = texturePnter[0];
				pnter[1] = texturePnter[1];
				pnter[2] = texturePnter[2];
				pnter[3] = texturePnter[3];
			}
			texturePnter += 4;
		}
		texturePnter += 4;
	}
}


Texture::~Texture()
{
	delete[] texture;
}
