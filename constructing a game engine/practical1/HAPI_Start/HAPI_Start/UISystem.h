#pragma once
#include <HAPI_lib.h>
#include "vector2.hpp"
#include "Window.h"

class UISystem
{
public:
	UISystem();

	//draws health number
	void drawHealth(int health, vector2 position, int entityHeight) { HAPI.RenderText((int)position.x, (int)position.y + entityHeight, HAPISPACE::HAPI_TColour::GREEN, "health: " + std::to_string(health)); }
	
	//draws a healthbar
	void drawHealthBar(int health, vector2 position, int entityHeight, Window& viz) { int x = (int)position.x; int y = (int)position.y + entityHeight; int height = 8; int width = health; viz.drawRectangle(x, y, width, height, HAPISPACE::HAPI_TColour::GREEN); }
	
	//shows what wave the player is on
	void drawWave(int waveNumber) { HAPI.RenderText(10, 10, HAPISPACE::HAPI_TColour::GREEN, "wave: " + std::to_string(waveNumber), 24); }
	
	//shows win or lose text
	void drawWin() { HAPI.RenderText(250, 200, HAPISPACE::HAPI_TColour::GREEN, "you win! press esc if you want to play again", 36); }
	void drawLose() { HAPI.RenderText(250, 200, HAPISPACE::HAPI_TColour::GREEN, "you have died! press esc if you wanna try again", 36); }
	~UISystem();
};

