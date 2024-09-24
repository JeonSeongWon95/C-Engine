#pragma once
#include "Scene_Level.h"

namespace Won
{
	class Scene_LevelManager
	{
	public:
		Scene_LevelManager();
		~Scene_LevelManager();

		template <typename T>
		static Scene_Level* CreateScene_Level(const std::wstring& Name);
		static Scene_Level* LoadScene_Level(const std::wstring& Name);

		static void Initialize();
		static void Update();
		static void LateUpdate();
		static void Render(HDC NewDC);
		static void Destroy();
		static Scene_Level* GetActiveScene() {return ActiveScene_Level;}
		static Scene_Level* GetDontDestoryOnScene() { return DontDestoryScene_Level; }


	private:
		static std::map<std::wstring, Scene_Level*> Scene_Levels;
		static Scene_Level* ActiveScene_Level;
		static Scene_Level* DontDestoryScene_Level;
	};

	template<typename T>
	inline Scene_Level* Scene_LevelManager::CreateScene_Level(const std::wstring& Name)
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

	inline Scene_Level* Scene_LevelManager::LoadScene_Level(const std::wstring& Name)
	{
		if (ActiveScene_Level != nullptr)
		{
			ActiveScene_Level->OnExit();
		}

		std::map<std::wstring, Scene_Level*>::iterator iter =
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

