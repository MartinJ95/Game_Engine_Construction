#include "star.h"

//default and overloaded constructer
star::star()
{
	m_X = (float)(rand() % 1000);
	m_Y = (float)(rand() % 1000);
	m_Z = (float)(rand() % 100);
}

star::star(float x, float y, float z) : m_X(x), m_Y(y), m_Z(z)
{

}

//resets position
void star::reset()
{
	m_X = (float)(rand() % 1000);
	m_Y = (float)(rand() % 1000);
	m_Z = (float)(rand() % 100);
}

//getter functions
float star::getX() const
{
	return m_X;
}

float star::getY() const
{
	return m_Y;
}

float star::getZ() const
{
	return m_Z;
}

//function to move the stars
void star::move(float x, float y, float z)
{
	m_X += x;
	m_Y += y;
	m_Z += z;
}

//render star onto screen
void star::render(Window &window, float &eyeDistance, float &Cx, float &Cy, HAPISPACE::HAPI_TColour &col) const
{
	int Sx = (int)(((eyeDistance * (m_X - Cx)) / (eyeDistance + m_Z)) + Cx);
	int Sy = (int)(((eyeDistance * (m_Y - Cy)) / (eyeDistance + m_Z)) + Cy);
	int Sradius = (int)(5 - ((m_Z/10)/2));
	window.drawCircle(Sx, Sy, Sradius, col);
}

star::~star()
{
}
