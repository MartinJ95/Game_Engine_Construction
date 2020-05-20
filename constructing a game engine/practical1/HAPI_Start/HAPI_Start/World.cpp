#include "World.h"
#include "Window.h"
#include "Entity.h"
#include "PlayerEntity.h"
#include "EnemyEntity.h"
#include "SceneryEntity.h"
#include "BulletEntity.h"
#include "vector2.hpp"
#include "AIWaveSystem.h"
#include "SoundSystem.h"
#include "UISystem.h"

#include <cassert>



World::World()
{
}

//loads the level
bool World::loadLevel()
{
	// load all sprites
	m_viz->CreateTexture("Data\\playerSprite.tga", "player");
	m_viz->CreateTexture("Data\\spaceBackground.png", "background");
	m_viz->CreateTexture("Data\\bullet.png", "bullet");
	m_viz->CreateTexture("Data\\explosion.png", "explosion", 4, 4);

	// loads sound
	soundSystem->loadSound("Data\\pew.wav");

	//loads entities
	SceneryEntity *newBackground = new SceneryEntity("background");
	newBackground->setPos(vector2(0, 0));
	newBackground->setSpeed(5.f);
	newBackground->setAlive(true);
	newBackground->setDimentions(m_viz->getTextureWidth("background"), m_viz->getTextureHeight("background"));
	m_entityVector.push_back(newBackground);

	for (int i = 0; i < 64; i++)
	{
		BulletEntity *newBullet = new BulletEntity("bullet");
		newBullet->setDimentions(m_viz->getTextureWidth("bullet"), m_viz->getTextureHeight("bullet"));
		newBullet->setHealth(1);
		newBullet->setSpeed(20.f);
		m_entityVector.push_back(newBullet);
	}

	for (int i = 0; i < 100; i++)
	{
		SceneryEntity *newExplosion = new SceneryEntity("explosion");
		newExplosion->setDimentions(m_viz->getTextureWidth("explosion"), m_viz->getTextureHeight("explosion"));
		newExplosion->setNumberOfFrames(m_viz->getTextureFrameNumber("explosion"));
		newExplosion->setAnimated(true);
		newExplosion->setAlpha(true);
		m_entityVector.push_back(newExplosion);
	}

	for (int i = 0; i < 5; i++)
	{
		EnemyEntity *newEnemy = new EnemyEntity("player");
		newEnemy->setDimentions(m_viz->getTextureWidth("player"), m_viz->getTextureHeight("player"));
		newEnemy->setAlpha(true);
		newEnemy->SetVariation(EVariation::eBasic);
		newEnemy->setRange(250);
		newEnemy->setHealth(50);
		newEnemy->setSpeed(15.f);
		m_entityVector.push_back(newEnemy);
	}

	for (int i = 0; i < 5; i++)
	{
		EnemyEntity *newEnemy = new EnemyEntity("player");
		newEnemy->setDimentions(m_viz->getTextureWidth("player"), m_viz->getTextureHeight("player"));
		newEnemy->setAlpha(true);
		newEnemy->SetVariation(EVariation::eSniper);
		newEnemy->setRange(500);
		newEnemy->setHealth(50);
		newEnemy->setSpeed(10.f);
		m_entityVector.push_back(newEnemy);
	}

	for (int i = 0; i < 5; i++)
	{
		EnemyEntity *newEnemy = new EnemyEntity("player");
		newEnemy->setDimentions(m_viz->getTextureWidth("player"), m_viz->getTextureHeight("player"));
		newEnemy->setAlpha(true);
		newEnemy->SetVariation(EVariation::eCharger);
		newEnemy->setRange(0);
		newEnemy->setHealth(100);
		newEnemy->setSpeed(10.f);
		m_entityVector.push_back(newEnemy);
	}

	for (int i = 0; i < 5; i++)
	{
		EnemyEntity *newEnemy = new EnemyEntity("player");
		newEnemy->setDimentions(m_viz->getTextureWidth("player"), m_viz->getTextureHeight("player"));
		newEnemy->setAlpha(true);
		newEnemy->SetVariation(EVariation::eCharger);
		newEnemy->setRange(0);
		newEnemy->setHealth(100);
		newEnemy->setSpeed(10.f);
		m_entityVector.push_back(newEnemy);
	}

	for (int i = 0; i < 5; i++)
	{
		EnemyEntity *newEnemy = new EnemyEntity("player");
		newEnemy->setDimentions(m_viz->getTextureWidth("player"), m_viz->getTextureHeight("player"));
		newEnemy->setAlpha(true);
		newEnemy->SetVariation(EVariation::eAdvanced);
		newEnemy->setRange(250);
		newEnemy->setHealth(100);
		newEnemy->setSpeed(15.f);
		m_entityVector.push_back(newEnemy);
	}

	EnemyEntity *newEnemy = new EnemyEntity("player");
	newEnemy->setDimentions(m_viz->getTextureWidth("player"), m_viz->getTextureHeight("player"));
	newEnemy->setAlive(true);
	newEnemy->setAlpha(true);
	newEnemy->setPos(vector2(500, 500));
	newEnemy->SetVariation(EVariation::eBasic);
	m_entityVector.push_back(newEnemy);


	PlayerEntity *newPlayer = new PlayerEntity("player");
	newPlayer->setPos(vector2(50, 50));
	newPlayer->setDimentions(m_viz->getTextureWidth("player"), m_viz->getTextureHeight("player"));
	newPlayer->setAlive(true);
	newPlayer->setAlpha(true);
	m_entityVector.push_back(newPlayer);


	return true;
}

// resets the game
void World::reset()
{
	for (auto e : m_entityVector)
	{
		e->setAlive(false);
		if (e->GetType() == EType::ePlayer)
		{
			e->setPos(vector2(50, 50));
			e->setAlive(true);
			e->setHealth(100);
		}
		else if (e->GetType() == EType::eScenery)
		{
			e->setPos(vector2(0, 0));
			e->setAlive(true);
		}
		else if (e->GetType() == EType::eEnemy)
		{
			e->setAlive(false);
		}
	}
	waveSystem->reset();
}

//tests to see if there are still remaining enemies
bool World::enemiesRemaining() const
{
	for (auto e : m_entityVector)
	{
		if (e->GetType() == EType::eEnemy && e->isAlive())
		{
			return true;
		}
	}
	return false;
}

//tick times
constexpr HAPISPACE::DWORD kTickTime{ 50 };
constexpr HAPISPACE::DWORD waveTimer{ 50000 };

//update for the world
void World::Update()
{
	HAPISPACE::DWORD lastTimeTicked{ 0 };
	HAPISPACE::DWORD lastWaveTime{ 0 };
	//soundSystem->playStreamedMedia("Data\\song.ogg");
	while (m_viz->update())
	{
		//clear screen
		m_viz->clear();

		//loads next wave either if no enemies are remaining or enough time has passed
		HAPISPACE::DWORD timeSinceLastWave{ HAPI.GetTime() - lastWaveTime };

		if (timeSinceLastWave >= waveTimer || !enemiesRemaining())
		{
			if (waveSystem->newWave())
			{
				waveData data = waveSystem->getNextWave();
				for (int i = 0; i < data.enemies; i++)
				{
					for (auto e : m_entityVector)
					{
						if (e->GetType() == EType::eEnemy && e->isAlive() == false)
						{
							if (e->GetVariation() == data.type[i])
							{
								if (data.side[i] == 0)
								{
									int position = 0 + (std::rand() % (int)m_viz->getHeight() - 0 + 1);
									e->setPos(vector2(0, (float)position));
								}
								else if (data.side[i] == 1)
								{
									int position = 0 + (std::rand() % (int)m_viz->getWidth() - 0 + 1);
									e->setPos(vector2((float)position, 0));
								}
								else if (data.side[i] == 2)
								{
									int position = 0 + (std::rand() % (int)m_viz->getHeight() - 0 + 1);
									e->setPos(vector2((float)m_viz->getWidth(), (float)position));
								}
								else if (data.side[i] == 3)
								{
									int position = 0 + (std::rand() % (int)m_viz->getWidth() - 0 + 1);
									e->setPos(vector2((float)position,(float) m_viz->getHeight()));
								}
								e->setAlive(true);
								break;
							}
						}
					}
				}
			}

			lastWaveTime = HAPI.GetTime();
			timeSinceLastWave = 0;
		}

		//entity updates every tick
		HAPISPACE::DWORD timeSinceLastTick{ HAPI.GetTime() - lastTimeTicked };

		if (timeSinceLastTick >= kTickTime)
		{
			for (auto p : m_entityVector)
			{
				if (p->isAlive())
				{
					if (p->GetSide() == ESide::eEnemy && p->GetType() != EType::eBullet)
					{
						for (auto o : m_entityVector)
						{
							if (o->GetType() == EType::ePlayer)
							{
								// sets enemies to aim at the player
								p->setAim(o->getPosition());
							}
						}
					}

					//entity update
					p->Update();

					//fire function for when the entity fires at their target
					if (p->Firing())
					{
						for (auto b : m_entityVector)
						{
							if (b->GetType() == EType::eBullet && b->isAlive() == false)
							{
								b->setAlive(true);
								b->setPos(p->getPosition());
								b->setMovement(p->getAim());
								b->SetSide(p->GetSide());
								b->setHealth(1);
								break;
							}
						}
						soundSystem->playSound("Data\\pew.wav");
					}
				}
			}

			lastTimeTicked = HAPI.GetTime();
			timeSinceLastTick = 0;
		}

		//variable for interpolation
		float s = timeSinceLastTick / (float)kTickTime;
		assert(s >= 0.f && s <= 1.f);

		// collision detection loop
		for (auto e : m_entityVector)
		{
			if (e->GetSide() != ESide::eNeutral && e->isAlive())
			{
				for (auto o : m_entityVector)
				{
					if (o->GetSide() != ESide::eNeutral && o->GetSide() != e->GetSide() && o->isAlive())
					{
						if (e->getX() + e->getWidth() < o->getX() || e->getX() > o->getX() + o->getWidth() || e->getY() + e->getHeight() < o->getY() || e->getY() > o->getY() + o->getHeight())
						{

						}
						else if (e->GetType() == EType::eBullet && o->GetType() == EType::eBullet)
						{

						}
						else
						{
							e->knockBack();
							o->knockBack();
							if (e->takeDamage(10))
							{
								for (auto p : m_entityVector)
								{
									if (p->GetType() == EType::eScenery && p->isAlive() == false)
									{
										p->setAlive(true);
										p->setPos(e->getPosition());
										p->setFrameNumber(1);
										break;
									}
								}
							}
							if (o->takeDamage(10))
							{
								for (auto p : m_entityVector)
								{
									if (p->GetType() == EType::eScenery && p->isAlive() == false)
									{
										p->setAlive(true);
										p->setPos(o->getPosition());
										p->setFrameNumber(1);
										break;
									}
								}
							}
						}
					}
				}
			}
		}

		//render loop for entities and ui
		for (auto p : m_entityVector)
		{
			if (p->GetType() == EType::ePlayer && !p->isAlive())
			{
				uiSystem->drawLose();
			}
			if (!enemiesRemaining() && !waveSystem->getWave())
			{
				uiSystem->drawWin();
			}
			if (p->isAlive())
			{
				p->Render(*m_viz, s);
				if (p->GetType() != EType::eBullet && p->GetType() != EType::eScenery)
				{
					//uiSystem->drawHealth(p->getHealth(), p->getInterpolatedPosition(s), p->getHeight());
					uiSystem->drawHealthBar((float)p->getHealth(), p->getInterpolatedPosition(s), p->getHeight(), *m_viz);
				}
			}
		}
		uiSystem->drawWave(waveSystem->getWave());
		const HAPISPACE::HAPI_TKeyboardData &keyData = HAPI.GetKeyboardData();
		if (keyData.scanCode[HK_ESCAPE])
		{
			reset();
		}
	}
}

void World::Run()
{
	m_viz = new Window(1260, 780);
	if (!m_viz->create())
		return;
	waveSystem = new AIWaveSystem;
	waveSystem->setUp();
	soundSystem = new SoundSystem;
	uiSystem = new UISystem;

	if (!loadLevel())
		return;
	HAPI.SetShowFPS(true);
	Update();
}

World::~World()
{
	delete m_viz;
	delete waveSystem;
	delete soundSystem;
	delete uiSystem;
	for (auto p : m_entityVector)
		delete p;
}


