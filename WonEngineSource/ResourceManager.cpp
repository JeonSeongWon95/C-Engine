#include "ResourceManager.h"

std::map<std::wstring, Won::WResource*> Won::ResourceManager::Resources = {};

Won::ResourceManager::ResourceManager()
{
}

Won::ResourceManager::~ResourceManager()
{
	for(std::map<std::wstring, WResource*>::iterator iter = Resources.begin();
		iter != Resources.end();)
	{
		delete iter->second;
		iter = Resources.erase(iter);
	}

	Resources.clear();
}
