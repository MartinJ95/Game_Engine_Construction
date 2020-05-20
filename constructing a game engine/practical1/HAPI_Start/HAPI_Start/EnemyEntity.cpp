#include "EnemyEntity.h"



EnemyEntity::EnemyEntity(std::string spriteName) : Entity(spriteName)
{
}

bool EnemyEntity::Firing()
{
	float distanceX = m_aim.x - m_position.x;
	float distanceY = m_aim.y - m_position.y;
	//if (distanceX > -m_range || distanceX < m_range && distanceY > -m_range || distanceY < m_range)
	if (withinRange(distanceX, (float)m_range) && withinRange(distanceY, (float)m_range))
	{
		HAPISPACE::DWORD timeSinceLastShot{ HAPI.GetTime() - lastTimeShot };
		if (timeSinceLastShot >= rateOfFire)
		{
			lastTimeShot = HAPI.GetTime();
			timeSinceLastShot = 0;
			m_aim = m_aim - m_position;
			m_aim.normaliseInPlace();
			return true;
		}
		return false;
	}
	return false;
}

void EnemyEntity::Update()
{
	float distanceX = m_aim.x - m_position.x;
	float distanceY = m_aim.y - m_position.y;
	//if (distanceX > -m_range || distanceX < m_range && distanceY > -m_range || distanceY < m_range)
	if (withinRange(distanceX, (float)m_range) && withinRange(distanceY, (float)m_range))
	{
		m_oldPosition = m_position;
	}
	else
	{
		m_movement = m_aim - m_position;
		m_movement.normaliseInPlace();
		setPosition(m_position + (m_movement * m_speed));
	}
}


EnemyEntity::~EnemyEntity()
{
}
