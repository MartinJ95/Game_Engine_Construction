#pragma once
#include "Entity.h"
#include "stdlib.h"

struct waveData
{
	int enemies;
	std::vector<int> side;
	std::vector<EVariation> type;
};

class AIWaveSystem
{
private:

	//current wave and container for all wave information
	int m_currentWave = 0;
	std::vector<waveData> m_waves;
	
public:
	AIWaveSystem();

	//sets up waves with random enemies with modifiers depending on wave number
	void setUp();

	//resets the waves to the first wave
	void reset() { m_currentWave = 0; }

	//tests to see if there is a wave that hasn't spawned yet
	bool newWave() const;

	//spawns current wave and moves to the next wave
	waveData getNextWave();

	//gets the current wave
	int getWave() const { return m_currentWave; }
	~AIWaveSystem();
};

