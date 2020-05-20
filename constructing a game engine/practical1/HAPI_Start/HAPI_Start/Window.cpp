#include "Window.h"
#include "Texture.h"


Window::Window(int screenWidth, int screenHeight) : m_ScreenWidth(screenWidth), m_ScreenHeight(screenHeight)
{

}

//creates window
bool Window::create()
{
	if (HAPI.Initialise(m_ScreenWidth, m_ScreenHeight, "working"))
	{
		return true;
	}
	else
	{
		std::cerr << "Could not initualize" << std::endl;
		return false;
	}
}

//updates screen
bool Window::update()
{
	if (HAPI.Update())
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Window::CreateTexture(const std::string & filename, const std::string &name, int numberOfFramesX, int numberOfFramesY)
{
	Texture *newTexture = new Texture{ filename, numberOfFramesX, numberOfFramesY };
	if (!newTexture->loadTexture())
	{
		delete newTexture;
		return false;
	}

	m_textureMap[name] = newTexture;

	return false;
}

//clears screen to black
void Window::clear()
{
	HAPISPACE::BYTE *screen = HAPI.GetScreenPointer();
	memset(screen, 0, m_ScreenWidth*m_ScreenHeight * 4);
}

//clears screen to a specific colour
void Window::clearToColour(HAPISPACE::HAPI_TColour& col)
{
	HAPISPACE::BYTE *screen = HAPI.GetScreenPointer();
	HAPISPACE::BYTE *pnter = screen;
	for (int i = 0; i < m_ScreenWidth * m_ScreenHeight; i++)
	{
		*(HAPISPACE::HAPI_TColour*)pnter = col;
		pnter += 4;
	}
}

//getters for width and height
int Window::getWidth() const
{
	return m_ScreenWidth;
}

int Window::getHeight() const
{
	return m_ScreenHeight;
}

int Window::getTextureWidth(const std::string & name) const
{
	if (m_textureMap.find(name) == m_textureMap.end())
		return 0;

	return m_textureMap.at(name)->getWidth();
}

int Window::getTextureHeight(const std::string & name) const
{
	if (m_textureMap.find(name) == m_textureMap.end())
		return 0;

	return m_textureMap.at(name)->getHeight();
}

int Window::getTextureFrameNumber(const std::string &name) const
{
	if (m_textureMap.find(name) == m_textureMap.end())
		return 0;

	return m_textureMap.at(name)->getFrameNumber();
}


// test to see if an x, y coordinate is on the screen
bool Window::isOnScreen(int &x, int &y) const
{
	if (x > 0 && x < m_ScreenWidth && y > 0 && y < m_ScreenHeight)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//draw functions for shapes and text
void Window::drawRectangle(int &x, int &y, int &width, int &height, HAPISPACE::HAPI_TColour &col) const
{
	HAPISPACE::BYTE *screen = HAPI.GetScreenPointer();
	for (int gy = y; gy <= y + height; gy++)
	{
		for (int gx = x; gx <= x + width; gx++)
		{
			if (isOnScreen(gx, gy))
			{
				if (gx < x + width && gx > x && gy < y + height && gy > y)
				{
					unsigned int offset = (gx + gy * m_ScreenWidth) * 4;
					HAPISPACE::BYTE *pnter = screen + offset;
					*(HAPISPACE::HAPI_TColour*)pnter = col;
				}
			}
		}
	}
}

void Window::drawCircle(int &ox, int &oy, int &radius, HAPISPACE::HAPI_TColour &col) const
{
	int originX = ox + radius;
	int originY = oy + radius;
	int pointX = 0;
	int pointY = 0;
	HAPISPACE::BYTE *screen = HAPI.GetScreenPointer();
	for (int y = -radius; y <= radius; y++)
	{
		for (int x = -radius; x <= radius; x++)
		{
			pointX = originX + x;
			pointY = originY + y;
			if (isOnScreen(pointX, pointY))
			{
				if (x*x + y * y <= radius * radius)
				{
					unsigned int offset = ((originX + x) + (originY + y) * m_ScreenWidth) * 4;
					HAPISPACE::BYTE *pnter = screen + offset;
					*(HAPISPACE::HAPI_TColour*)pnter = col;
					/*pnter[0] = col.red;
					pnter[1] = col.green;
					pnter[2] = col.blue;
					pnter[3] = col.alpha;*/
				}
			}
		}
	}
}

void Window::drawText(int &x, int &y, std::string &text, HAPISPACE::HAPI_TColour &col, int size) const
{
	HAPI.RenderText(x, y, col, text, size);
}

void Window::render(const std::string & name, int posX, int posY, int frameNumber)
{
	if (m_textureMap.find(name) == m_textureMap.end())
		return;

	m_textureMap.at(name)->renderTexture(m_ScreenWidth, m_ScreenHeight, posX, posY, frameNumber);
}

void Window::renderWithAlpha(const std::string & name, int posX, int posY, int frameNumber)
{
	if (m_textureMap.find(name) == m_textureMap.end())
		return;

	m_textureMap.at(name)->renderTextureWithAlpha(m_ScreenWidth, m_ScreenHeight, posX, posY, frameNumber);
}


//function to set fps to showing/not showing
void Window::setFPS(bool &set, int &x, int &y, HAPISPACE::HAPI_TColour &col) const
{
	HAPI.SetShowFPS(set, x, y, col);
}

//return pointer to top left of screen
HAPISPACE::BYTE* Window::getScreen() const
{
	return HAPI.GetScreenPointer();
}

Window::~Window()
{
	for (auto it = m_textureMap.begin(); it != m_textureMap.end(); it++)
	{
		delete it->second;
	}
}
