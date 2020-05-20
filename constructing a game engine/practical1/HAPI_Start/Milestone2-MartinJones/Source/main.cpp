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
#include <iostream>

// HAPI itself is wrapped in the HAPISPACE namespace
using namespace HAPISPACE;

#if defined(DEBUG) | defined(_DEBUG)
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK,__FILE__, __LINE__)
#endif

// Every HAPI program has a HAPI_Main as an entry point
// When this function exits the program will close down
void HAPI_Main()
{
	//stars Stars(1000, 800, 400, 300, 100);
	//Stars.run();

	Window window(1260, 800);
	if (!window.create())
	{
		return;
	}
	float x = 50;
	float y = 50;
	int textureWidth = 64;
	int textureHeight = 64;
	std::string filePath = "Data\\alphaThing.tga";
	Texture texture(filePath, textureWidth, textureHeight);
	float secondX = 50;
	float secondY = 50;
	int secondTextureWidth = 256;
	int secondTextureHeight = 256;
	std::string secondFilePath = "Data\\background.tga";
	Texture secondTexture(secondFilePath, secondTextureWidth, secondTextureHeight);
	if (!texture.loadTexture())
	{
		return;
	}
	if (!secondTexture.loadTexture())
	{
		return;
	}
	HAPI.SetShowFPS(true);
	while (window.update())
	{
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
		window.clear();
		secondTexture.renderTexture(window, (int)secondX, (int)secondY);
		texture.renderTextureWithAlpha(window, (int)x, (int)y);
	}
}

//todo
//window draw pixel functions
//texture rotate functions
//engine structure planning