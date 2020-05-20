#include "BulletEntity.h"



BulletEntity::BulletEntity(std::string spriteName) : Entity(spriteName)
{
	m_isBullet = true;
}

void BulletEntity::Update()
{
	if (m_health <= 0)
	{
		m_alive = false;
		return;
	}
	setPosition(vector2(m_position.x + (m_movement.x * m_speed), m_position.y + (m_movement.y * m_speed)));
}

BulletEntity::~BulletEntity()
{
}
