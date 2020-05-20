#include "SceneryEntity.h"



SceneryEntity::SceneryEntity(std::string spriteName) : Entity(spriteName)
{
	m_isScenery = true;
}

void SceneryEntity::Update()
{
	vector2 pos{ getPosition() };
	const HAPISPACE::HAPI_TKeyboardData &keyData = HAPI.GetKeyboardData();
	if (keyData.scanCode[HK_DOWN])
	{
		pos.y -= m_speed;
	}
	if (keyData.scanCode[HK_UP])
	{
		pos.y += m_speed;
	}
	if (keyData.scanCode[HK_LEFT])
	{
		pos.x += m_speed;
	}
	if (keyData.scanCode[HK_RIGHT])
	{
		pos.x -= m_speed;
	}
	const HAPISPACE::HAPI_TControllerData &data = HAPI.GetControllerData(0);
	if (data.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] > 8291 || data.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] < -8192)
	{
		m_movement.x = (float)data.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X];
	}
	if (data.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] > 8191 || data.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] < -8192)
	{
		m_movement.y = (float)-data.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y];
	}
	if (m_movement.x != 0 || m_movement.y != 0)
	{
		m_movement.normaliseInPlace();
		pos.x -= m_movement.x * m_speed;
		pos.y -= m_movement.y * m_speed;
	}

	setPosition(pos);

	if (m_movement.x != 0 || m_movement.y != 0)
	{
		m_movement = vector2(0.f, 0.f);
		//movement.setX(0);
		//movement.setY(0);
	}
}


SceneryEntity::~SceneryEntity()
{
}
