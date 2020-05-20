#pragma once

#include"vector2.hpp"
#include <string>
#include <HAPI_lib.h>

class Window;

//types of enemies
enum class EVariation
{
	eBasic,
	eSniper,
	eCharger,
	eAdvanced
};

//type of entity
enum class EType
{
	ePlayer,
	eEnemy,
	eBullet,
	eScenery
};

//which side the entity is on
enum class ESide
{
	ePlayer,
	eEnemy,
	eNeutral
};

class Entity
{
protected:
	int m_health = 100;
	bool m_invincible{ false };
	int m_maxHealth = 100;
	int m_width;
	int m_height;
	int m_range{ 300 };
	vector2 m_position;
	vector2 m_oldPosition;
	vector2 m_movement{ 0,0 };
	vector2 m_aim{ 0,0 };
	vector2 m_destination{ 0,0 };
	int m_destinationNum{ 1 };
	float m_speed{10.f};
	std::string m_spriteName;
	int m_numOfFrames{ 1 };
	int m_frameNum{ 1 };
	bool m_alive{false};
	bool m_alpha{false};
	bool m_isBullet{ false };
	bool m_isScenery{ false };
	bool m_animated{ false };
	HAPISPACE::DWORD animationTime{ 50 };
	HAPISPACE::DWORD lastTimeAnimated{ 0 };
public:
	Entity(std::string spriteName);

	//renders the entity
	void Render(Window& viz, float s);

	//sets the position of the entity
	void setPosition(vector2 newPos) { m_oldPosition = m_position; m_position = newPos; }
	void setPos(vector2 newPos) { m_oldPosition = newPos; m_position = newPos; }

	//knocks the entity back to its old position
	void knockBack() { m_position = m_oldPosition + (m_oldPosition - m_position); m_oldPosition = m_position; }

	//sets the direction that the entity is moving
	void setMovement(vector2 direction) { m_movement = direction; }

	//sets where the entity is aiming at
	void setAim(vector2 aim) { m_aim = aim; }

	//sets the range at which the entity starts shooting at its target
	void setRange(int range) { m_range = range; }

	////sets the destination that the entity is moving to
	void setDestination(vector2 destination) { m_destination = destination; }

	//sets which destination the entity is moving toward
	void setDestinationNum(int destNum) { m_destinationNum = destNum; }

	//sets the width and height of the entity
	void setDimentions(int width, int height) { m_width = width; m_height = height; }

	//sets the speed of the entity
	void setSpeed(float speed) { m_speed = speed; }

	//sets the alpha blending state of the entity
	void setAlpha(bool alpha) { m_alpha = alpha; };

	//sets the alive state of the entity
	void setAlive(bool alive) { m_alive = alive; }

	//sets the animation state of the entity
	void setAnimated(bool animated) { m_animated = animated; }

	//sets which frame the entity is at in the animation
	void setFrameNumber(int frameNum) { m_frameNum = frameNum; }

	//sets the amount of frames in the entities animation
	void setNumberOfFrames(int numberOfFrames) { m_numOfFrames = numberOfFrames; }

	//sets the entity health value
	void setHealth(int health) { m_health = health; m_maxHealth = health; }

	//sets the invincibility state of the entity
	void setInvincible() { m_invincible = !m_invincible; }

	//entty takes damage to health and returns a true value if the entity dies
	bool takeDamage(int damage) { if (!m_invincible) { m_health -= damage; } if (m_health <= 0) { m_alive = false; m_health = m_maxHealth; return true; } return false; }

	//gets the name of the sprite attached to the entity
	std::string getSpriteName() const { return m_spriteName; }

	//getters for various values
	vector2 getPosition() const { return m_position; }
	vector2 getMovement() const { return m_movement; }
	vector2 getAim() const { return m_aim; }
	vector2 getInterpolatedPosition(const float s) { return  m_oldPosition + (m_position - m_oldPosition)*s; }
	int getRange() const { return m_range; }
	int getHealth() const { return m_health; }
	float getX() const { return m_position.getX(); }
	float getY() const { return m_position.getY(); }
	float getWidth() const { return (float)m_width; }
	float getHeight() const { return (float)m_height; }
	bool isAlive() const { return m_alive; }
	bool destinationReached() const { float x = m_destination.x - m_position.x; float y = m_destination.y - m_position.y; if (x > -5 || x < 5 && y > -5 || y < 5) { return true; } return false; }
	int getDestinationNum() const { return m_destinationNum; };

	virtual void Update() = 0;
	virtual bool Firing() = 0;
	virtual ESide GetSide() const = 0;
	virtual void SetSide(ESide side) = 0;
	virtual void SetType(EType type) = 0;
	virtual EType GetType() const = 0;
	virtual void SetVariation(EVariation) = 0;
	virtual EVariation GetVariation() = 0;

	virtual ~Entity();
};

