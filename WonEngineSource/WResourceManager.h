#pragma once

#include "includeHeader.h"
#include "WResource.h"

namespace Won
{
	class WResourceManager
	{
	public:
		WResourceManager();
		~WResourceManager();

		template<typename T>
		static T* Find(const std::wstring& FileName)
		{
			std::map<std::wstring, WResource*>::iterator iter = Resources.find(FileName);

			if (iter == Resources.end())
				return nullptr;

			return dynamic_cast<T*>(iter->second);
		}

		template<typename T>
		static T* Load(const std::wstring& FileName,const std::wstring& Path)
		{
			T* resource = WResourceManager::Find<T>(FileName);

			if (resource != nullptr)
				return resource;

			resource = new T();

			if(FAILED(resource->Load(Path)))
				assert(false);

			resource->SetName(FileName);
			resource->SetPath(Path);

			WResourceManager::Resources.insert(std::make_pair(FileName, resource));

			return resource;
		}

		static void Release()
		{
			for(auto& iter : Resources)
			{
				delete iter.second;
				iter.second = nullptr;
			}
		}

	private:
		static std::map<std::wstring, WResource*> Resources;
	};
}

