#include "WFmod.h"


FMOD::Studio::System* Won::WFmod::mSystem = nullptr;
FMOD::System* Won::WFmod::mCoreSystem = nullptr;

void Won::WFmod::Initialize()
{
	void* extraDriverData = nullptr;

	FMOD::Studio::System::create(&mSystem);
	mSystem->getCoreSystem(&mCoreSystem);
	mCoreSystem->setSoftwareFormat(0, FMOD_SPEAKERMODE_5POINT1, 0);
}

bool Won::WFmod::CreateSound(const std::string& path, FMOD::Sound* sound)
{
	if(FMOD_OK == mCoreSystem->createSound(path.c_str(), FMOD_3D, 0, &sound))
	{
		return true;
	}

	return false;
}

void Won::WFmod::SoundPlay(FMOD::Sound* sound, FMOD::Channel** channel)
{
	mCoreSystem->playSound(sound, 0, false, channel);
}
