#pragma once
#include "WScene.h"

namespace Won
{
	class WSceneManager
	{
	public:
		WSceneManager();
		~WSceneManager();

		template <typename T>
		static WScene* CreateScene_Level(const std::wstring& Name);
		static WScene* LoadScene_Level(const std::wstring& Name);

		static void Initialize();
		static void Update();
		static void LateUpdate();
		static void Render(HDC NewDC);
		static void Destroy();
		static WScene* GetActiveScene() {return ActiveScene_Level;}
		static WScene* GetDontDestoryOnScene() { return DontDestoryScene_Level; }
		static std::vector<class WGameObject*> GetGameObjects(eLayerType NewLayer);


	private:
		static std::map<std::wstring, WScene*> Scene_Levels;
		static WScene* ActiveScene_Level;
		static WScene* DontDestoryScene_Level;
	};

	template<typename T>
	inline WScene* WSceneManager::CreateScene_Level(const std::wstring& Name)
	{
		{
			T* NewLevel = new T;
			NewLevel->SetName(Name);
			ActiveScene_Level = NewLevel;
			NewLevel->Initialize();

			Scene_Levels.insert(std::make_pair(Name, NewLevel));

			return NewLevel;

		}
	}

	inline WScene* WSceneManager::LoadScene_Level(const std::wstring& Name)
	{
		if (ActiveScene_Level != nullptr)
		{
			ActiveScene_Level->OnExit();
		}

		std::map<std::wstring, WScene*>::iterator iter =
			Scene_Levels.find(Name);

		if (iter == Scene_Levels.end())
		{
			return nullptr;
		}

		ActiveScene_Level = iter->second;

		ActiveScene_Level->OnEnter();

		return ActiveScene_Level;
	}
}

