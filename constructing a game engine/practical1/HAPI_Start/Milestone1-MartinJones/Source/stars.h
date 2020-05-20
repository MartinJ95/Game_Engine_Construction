#pragma once

#include "Window.h"
#include "star.h"
#include <stdlib.h>
#include <time.h>

class stars
{
private:
	//screen variables
	int m_ScreenWidth, m_ScreenHeight;

	//camera variables
	float m_CameraX, m_CameraY, m_eyeDistance;
	float speed = 0.5;

	//fps variables
	bool fps = true;
	int fpsX = 50;
	int fpsY = 50;

	//title variables
	std::string title = "stars!";
	int titleX;
	int titleY;
	int titleTextSize = 40;
public:
	stars(int screenWidth, int screenHeight, float cameraX, float cameraY, float eyeDistance);
	//main function for stars project
	void run();
	~stars();
};

