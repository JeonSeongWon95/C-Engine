#include "WAudioClip.h"

Won::WAudioClip::WAudioClip()
	:WResource(eResourceType::Audio)
	, mSound(nullptr)
	, mChannel(nullptr)
{
}

Won::WAudioClip::~WAudioClip()
{
}

HRESULT Won::WAudioClip::Load(const std::wstring& NewPath)
{
	std::string cpath(NewPath.begin(), NewPath.end());

	if(WFmod::CreateSound(cpath, mSound))
	{
		return S_OK;
	}

	return S_FALSE;
}
