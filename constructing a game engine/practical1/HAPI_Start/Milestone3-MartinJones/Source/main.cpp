/*
	HAPI Start
	----------
	This solution contains an already set up HAPI project and this main file
	
	The directory structure and main files are:

	HAPI_Start - contains the Visual Studio solution file (.sln)
		HAPI_Start - contains the Visual Studio HAPI_APP project file (.vcxproj) and source code
			HAPI - the directory with all the HAPI library files
			Data - a place to put your data files with a few sample ones provided

	Additionally in the top directory there is a batch file for creating a redistributable Demo folder

	For help using HAPI:
	https://scm-intranet.tees.ac.uk/users/u0018197/hapi.html
*/

// Include the HAPI header to get access to all of HAPIs interfaces
#include <HAPI_lib.h>
#include "Window.h"
#include "stars.h"
#include "Texture.h"
#include "vector2.hpp"
#include <iostream>

// HAPI itself is wrapped in the HAPISPACE namespace
using namespace HAPISPACE;

#if defined(DEBUG) | defined(_DEBUG)
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK,__FILE__, __LINE__)
#endif

Window window(1260, 800);

// Every HAPI program has a HAPI_Main as an entry point
// When this function exits the program will close down
void HAPI_Main()
{
	//stars Stars(1000, 800, 400, 300, 100);
	//Stars.run();


	DWORD timesincelasttick = 0;
	int animationNumber = 1;
	
	if (!window.create())
	{
		return;
	}
	float x = 50;
	float y = 50;
	static vector2 movement;
	//int textureWidth = 64;
	//int textureHeight = 64;
	//std::string filePath = "Data\\alphaThing.tga";
	//Texture texture(filePath);
	window.CreateTexture("Data\\alphaThing.tga", "player", 2, 2);
	float secondX = 100;
	float secondY = 100;
	//int secondTextureWidth = 256;
	//int secondTextureHeight = 256;
	//std::string secondFilePath = "Data\\background.tga";
	//Texture secondTexture(secondFilePath);
	window.CreateTexture("Data\\background.tga", "background");
	/*if (!texture.loadTexture())
	{
		return;
	}
	if (!secondTexture.loadTexture())
	{
		return;
	}*/
	HAPI.SetShowFPS(true);
	while (window.update())
	{
		if (HAPI.GetTime() - timesincelasttick > 200)
		{
			if (animationNumber >= 4)
			{
				animationNumber = 1;
			}
			else
			{
				animationNumber++;
			}
			timesincelasttick = HAPI.GetTime();
		}
		const HAPISPACE::HAPI_TKeyboardData &keyData = HAPI.GetKeyboardData();
		if (keyData.scanCode[HK_DOWN])
		{
			y += 1.f;
		}
		if (keyData.scanCode[HK_UP])
		{
			y -= 1.f;
		}
		if (keyData.scanCode[HK_LEFT])
		{
			x -= 1.f;
		}
		if (keyData.scanCode[HK_RIGHT])
		{
			x += 1.f;
		}
		const HAPISPACE::HAPI_TControllerData &data = HAPI.GetControllerData(0);
		if (data.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] > 8291 || data.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] < -8192)
		{
			movement.x = (float)data.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X];
		}
		if (data.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] > 8191 || data.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] < -8192)
		{
			movement.y = (float)-data.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y];
		}
		if (movement.x != 0 || movement.y != 0)
		{
			movement.normaliseInPlace();
			x += movement.x;
			y += movement.y;
		}
		window.clear();
		//secondTexture.renderTexture(window.getWidth(), window.getHeight(), (int)secondX, (int)secondY, 1);
		window.render("background", (int)secondX, (int)secondY);
		//texture.renderTextureWithAlpha(window.getWidth(), window.getHeight(), (int)x, (int)y, 1);
		window.renderWithAlpha("player", (int)x, (int)y, animationNumber);
		if (movement.x != 0 || movement.y != 0)
		{
//			movement = vector2(0, 0);
			movement.setX(0);
			movement.setY(0);
		}
		if (window.getWidth() >> 1 > x && window.getWidth() >> 1 < x + window.getTextureWidth("player"))
		{
			HAPI.SetControllerRumble(0, 10000, 10000);
		}
		else if (window.getHeight() >> 1 > y && window.getHeight() >> 1 < y + window.getTextureHeight("player"))
		{
			HAPI.SetControllerRumble(0, 10000, 10000);
		}
		else
		{
			HAPI.SetControllerRumble(0, 0, 0);
		}
	}
}

//todo
//window draw pixel functions
//texture rotate functions
//engine structure planning