#pragma once

#include <HAPI_lib.h>
#include <unordered_map>

class Texture;

class Window
{
private:
	int m_ScreenWidth, m_ScreenHeight;

	HAPISPACE::BYTE *screen{ nullptr };

	std::unordered_map<std::string, Texture*> m_textureMap;
private:
	// test to see if an x, y coordinate is on the screen
	bool isOnScreen(int &x, int &y) const;
public:
	Window(int screenWidth, int screenHeight);
	//creates window
	bool create();

	//updates screen
	bool update();

	bool CreateTexture(const std::string &filename, const std::string &name , int numberOfFramesX = 1, int numberOfFramesY = 1);

	//clears screen to black
	void clear();

	//clears screen to a specific colour
	void clearToColour(HAPISPACE::HAPI_TColour& col);

	//getters for width and height
	int getWidth() const;
	int getHeight() const;

	int getTextureWidth(const std::string &name) const;
	int getTextureHeight(const std::string &name) const;

	//draw functions for shapes and text
	void drawRectangle(int &x, int &y, int &width, int &height, HAPISPACE::HAPI_TColour &col) const;
	void drawCircle(int &x, int &y, int &radius, HAPISPACE::HAPI_TColour &col) const;
	void drawText(int &x, int &y, std::string &text, HAPISPACE::HAPI_TColour &col, int size) const;

	//draw functions for textures
	void render(const std::string &name, int posX, int posY, int frameNumber = 1);
	void renderWithAlpha(const std::string &name, int posX, int posY, int frameNumber = 1);

	//function to set fps to showing/not showing
	void setFPS(bool &set, int &x, int &y, HAPISPACE::HAPI_TColour &col) const;

	//return pointer to top left of screen
	HAPISPACE::BYTE* getScreen() const;


	~Window();
};

