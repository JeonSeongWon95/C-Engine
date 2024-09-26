#pragma once
#include "includeHeader.h"
#include "../External/Include/Fmod/fmod_common.h"
#include "../External/Include/Fmod/fmod.hpp"
#include "../External/Include/Fmod/fmod_codec.h"
#include "../External/Include/Fmod/fmod_studio.hpp"

#ifdef _DEBUG
#pragma comment(lib, "../External/Library/Fmod/Debug/fmodL_vc.lib")
#pragma comment(lib, "../External/Library/Fmod/Debug/fmodstudioL_vc.lib")
#else
#pragma comment(lib, "../External/Library/Fmod/Release/fmod_vc.lib")
#pragma comment(lib, "../External/Library/Fmod/Release/fmodstudio_vc.lib")
#endif


namespace Won
{
	class WFmod
	{
	public:
		static void Initialize();
		static bool CreateSound(const std::string& path, FMOD::Sound* sound);
		static void SoundPlay(FMOD::Sound* sound, FMOD::Channel** channel);

	private:
		static FMOD::Studio::System* mSystem;
		static FMOD::System* mCoreSystem;
	};
}

