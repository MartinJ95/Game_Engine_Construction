#pragma once
#include <HAPI_lib.h>

class SoundSystem
{
private:

public:
	SoundSystem();

	//loads a sound from the resource folder by filename
	bool loadSound(const std::string &filename);

	//plays a loaded sound
	bool playSound(const std::string &filename);

	//streams a sound file from the resource folder by filename
	bool playStreamedMedia(const std::string &filename);
	~SoundSystem();
};

