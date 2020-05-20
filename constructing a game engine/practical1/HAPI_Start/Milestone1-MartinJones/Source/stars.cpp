#include "stars.h"



stars::stars(int screenWidth, int screenHeight, float cameraX, float cameraY, float eyeDistance) : m_ScreenWidth(screenWidth), m_ScreenHeight(screenHeight), m_CameraX(cameraX), m_CameraY(cameraY), m_eyeDistance(eyeDistance)
{
	titleX = (screenWidth / 2) - titleTextSize;
	titleY = (screenHeight / 2) - titleTextSize;
}

void stars::run()
{
	// seeding the random
	srand((unsigned int)time(NULL));

	//creating the window objects
	Window window(m_ScreenWidth, m_ScreenHeight);

	//returns error if window creation returns error
	if (!window.create())
	{
		return;
	}

	//clearing the window
	window.clear();

	//color of stars
	HAPISPACE::HAPI_TColour col(255, 255, 255);
	HAPISPACE::HAPI_TColour bcol(32, 32, 128);

	//star amount
	const int StarAmount = 1000;

	//creates the amount of stars
	star Stars[StarAmount];
	
	//sets fps
	window.setFPS(fps, fpsX, fpsY, col);
	while (window.update())
	{
		//keyboard input manager
		const HAPISPACE::HAPI_TKeyboardData &keyData = HAPI.GetKeyboardData();
		if (keyData.scanCode[HK_DOWN])
		{
			if (speed > (float)0.1)
			{
				speed -= (float)0.01;
			}
		}
		if (keyData.scanCode[HK_UP])
		{
			if (speed < 2)
			{
				speed += (float)0.01;
			}
		}
		if (keyData.scanCode[HK_LEFT])
		{
			if (m_eyeDistance > 10)
			{
				m_eyeDistance -= (float)0.1;
			}
		}
		if (keyData.scanCode[HK_RIGHT])
		{
			if (m_eyeDistance < 200)
			{
				m_eyeDistance += (float)0.1;
			}
		}
		if (keyData.scanCode['W'])
		{
			m_CameraY += 0.5;
		}
		if (keyData.scanCode['A'])
		{
			m_CameraX -= 0.5;
		}
		if (keyData.scanCode['S'])
		{
			m_CameraY -= 0.5;
		}
		if (keyData.scanCode['D'])
		{
			m_CameraX += 0.5;
		}

		//clearing window
		window.clearToColour(bcol);

		//loop to iterate through the stars functions
		for (int i = 0; i < StarAmount; i++)
		{
			//moves stars closer to screen
			Stars[i].move(0, 0, -speed);

			//testing the stars z
			if (Stars[i].getZ() <= 0)
			{
				Stars[i].reset();
			}

			//rendering the stars
			Stars[i].render(window, m_eyeDistance, m_CameraX, m_CameraY, col);
		}
		window.drawText(titleX, titleY, title, col, titleTextSize);
	}
}

stars::~stars()
{

}
