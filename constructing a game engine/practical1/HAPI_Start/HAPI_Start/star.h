#pragma once

#include "Window.h"
#include <stdlib.h>

class star
{
private:
	//coordinates
	float m_X, m_Y, m_Z;
public:
	//default and overloaded constructer
	star();
	star(float x, float y, float z);

	//resets position
	void reset();

	//getter functions
	float getX() const;
	float getY() const;
	float getZ() const;

	//function to move the stars
	void move(float x, float y, float z);

	//render star onto screen
	void render(Window &window, float &eyeDistance, float &Cx, float &Cy, HAPISPACE::HAPI_TColour &col) const;
	~star();
};

