#include "SoundSystem.h"



SoundSystem::SoundSystem()
{
}

//loads a sound from the resource folder by filename
bool SoundSystem::loadSound(const std::string & filename)
{
	if (!HAPI.LoadSound(filename))
	{
		HAPI.UserMessage("missing sound: " + filename, "failed to load sound");
		return false;
	}
	return true;
}

//plays a loaded sound
bool SoundSystem::playSound(const std::string & filename)
{
	if (!HAPI.PlaySound(filename))
	{
		HAPI.UserMessage("missing sound " + filename, "failed to play sound");
		return false;
	}
	return true;
}

//streams a sound file from the resource folder by filename
bool SoundSystem::playStreamedMedia(const std::string & filename)
{
	if (!HAPI.PlayStreamedMedia(filename))
	{
		HAPI.UserMessage("missing sound " + filename, "failed to play sound");
		return false;
	}
	return true;
}


SoundSystem::~SoundSystem()
{
}
