#pragma once

#include <HAPI_lib.h>

class Window
{
private:
	int m_ScreenWidth, m_ScreenHeight;
private:
	// test to see if an x, y coordinate is on the screen
	bool isOnScreen(int &x, int &y) const;
public:
	Window(int screenWidth, int screenHeight);
	//creates window
	bool create();

	//updates screen
	bool update();

	//clears screen to black
	void clear();

	//clears screen to a specific colour
	void clearToColour(HAPISPACE::HAPI_TColour& col);

	//getters for width and height
	int getWidth() const;
	int getHeight() const;

	//draw functions for shapes and text
	void drawRectangle(int &x, int &y, int &width, int &height, HAPISPACE::HAPI_TColour &col) const;
	void drawCircle(int &x, int &y, int &radius, HAPISPACE::HAPI_TColour &col) const;
	void drawText(int &x, int &y, std::string &text, HAPISPACE::HAPI_TColour &col, int size) const;

	//function to set fps to showing/not showing
	void setFPS(bool &set, int &x, int &y, HAPISPACE::HAPI_TColour &col) const;

	//return pointer to top left of screen
	HAPISPACE::BYTE* getScreen() const;
	~Window();
};

