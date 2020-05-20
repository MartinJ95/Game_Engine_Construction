#include "AIWaveSystem.h"



AIWaveSystem::AIWaveSystem()
{
}

//sets up waves with random enemies with modifiers depending on wave number
void AIWaveSystem::setUp()
{
	for (int i = 0; i < 20; i++)
	{
		waveData wave;
		if (i < 5)
		{
			wave.enemies = i + 1;
		}
		else
		{
			wave.enemies = 5;
		}
		for (int t = 0; t < wave.enemies; t++)
		{
			wave.side.push_back(0 + (std::rand() % (3 - 0 + 1)));
		}
		for (int t = 0; t < wave.enemies; t++)
		{
			int type;
			if (i < 5)
			{
				type = 0 + (std::rand() % (1 - 0 + 1));				
			}
			else if (i < 10)
			{
				type = 0 + (std::rand() % (2 - 0 + 1));
			}
			else if (i < 15)
			{
				type = 1 + (std::rand() % (3 - 1 + 1));
			}
			else
			{
				type = 2 + (std::rand() % (3 - 2 + 1));
			}
			if (type == 0)
			{
				wave.type.push_back(EVariation::eBasic);
			}
			else if (type == 1)
			{
				wave.type.push_back(EVariation::eSniper);
			}
			else if (type == 2)
			{
				wave.type.push_back(EVariation::eCharger);
			}
			else if (type == 3)
			{
				wave.type.push_back(EVariation::eAdvanced);
			}
		}
		m_waves.push_back(wave);
	}
}

//tests to see if there is a wave that hasn't spawned yet
bool AIWaveSystem::newWave() const
{
	if (m_currentWave < m_waves.size())
	{
		return true;
	}
	return false;
}

//spawns current wave and moves to the next wave
waveData AIWaveSystem::getNextWave()
{
	m_currentWave++;
	return m_waves[m_currentWave - 1];
}

AIWaveSystem::~AIWaveSystem()
{
}
