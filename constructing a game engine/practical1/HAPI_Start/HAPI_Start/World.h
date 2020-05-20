#pragma once
#include <HAPI_lib.h>
#include <vector>
class Window;
class Entity;
class AIWaveSystem;
class SoundSystem;
class UISystem;

class World
{
private:
	Window *m_viz{ nullptr };
	AIWaveSystem *waveSystem{ nullptr };
	SoundSystem *soundSystem{ nullptr };
	UISystem *uiSystem{ nullptr };

	//container for entities
	std::vector<Entity*> m_entityVector;
private:
	//tests to see if enemies are remaining
	bool enemiesRemaining() const;

	// loads the level
	bool loadLevel();

	// world update
	void Update();

	// resets to start of the level
	void reset();
public:
	World();
	~World();

	//runs the system
	void Run();
};

