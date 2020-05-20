#include "Entity.h"
#include "Window.h"



Entity::Entity(std::string spriteName) : m_spriteName(spriteName)
{
}

void Entity::Render(Window& viz, float s)
{
	if (m_animated)
	{
		HAPISPACE::DWORD timeSinceLastAnimate{ HAPI.GetTime() - lastTimeAnimated };
		if (timeSinceLastAnimate >= animationTime)
		{
			if (m_frameNum >= m_numOfFrames)
			{
				m_alive = false;
				m_frameNum = 1;
				return;
			}
			else
			{
				m_frameNum++;
				lastTimeAnimated = HAPI.GetTime();
				timeSinceLastAnimate = 0;
			}
		}
	}
	if (m_isBullet)
	{
		if (m_position.x < 0 || m_position.x > viz.getWidth() || m_position.y < 0 || m_position.y > viz.getHeight())
		{
			m_alive = false;
		}
	}
	vector2 interpolatedPosition{ m_oldPosition + (m_position - m_oldPosition)*s };
	if (!m_alpha)
	{
		viz.render(m_spriteName, (int)interpolatedPosition.x, (int)interpolatedPosition.y, m_frameNum);
	}
	else
	{
		viz.renderWithAlpha(m_spriteName, (int)interpolatedPosition.x, (int)interpolatedPosition.y, m_frameNum);
	}
	/*if (!m_isBullet && !m_isScenery)
	{
		HAPI.RenderText(interpolatedPosition.x, interpolatedPosition.y + m_height, HAPISPACE::HAPI_TColour::GREEN, "health = " + std::to_string(m_health));
	}*/
}


Entity::~Entity()
{
}
