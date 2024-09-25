#include "WResourceManager.h"

std::map<std::wstring, Won::WResource*> Won::WResourceManager::Resources = {};

Won::WResourceManager::WResourceManager()
{
}

Won::WResourceManager::~WResourceManager()
{
	for(std::map<std::wstring, WResource*>::iterator iter = Resources.begin();
		iter != Resources.end();)
	{
		delete iter->second;
		iter = Resources.erase(iter);
	}

	Resources.clear();
}
