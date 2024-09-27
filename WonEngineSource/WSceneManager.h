#pragma once
#include "WScene.h"

namespace Won
{
	class WSceneManager
	{
	public:
		template <typename T>
		static WScene* CreateScene(const std::wstring& Name);
		static WScene* LoadScene(const std::wstring& Name);

		static void Initialize();
		static void Update();
		static void LateUpdate();
		static void Render(HDC NewDC);
		static void Destroy();
		static void Release();
		static WScene* GetActiveScene() {return ActiveScene;}
		static WScene* GetDontDestoryOnScene() { return DontDestoryScene; }
		static std::vector<class WGameObject*> GetGameObjects(eLayerType NewLayer);


	private:
		static std::map<std::wstring, WScene*> Scenes;
		static WScene* ActiveScene;
		static WScene* DontDestoryScene;
	};

	template<typename T>
	inline WScene* WSceneManager::CreateScene(const std::wstring& Name)
	{
		{
			T* NewLevel = new T;
			NewLevel->SetName(Name);
			ActiveScene = NewLevel;
			NewLevel->Initialize();

			Scenes.insert(std::make_pair(Name, NewLevel));

			return NewLevel;

		}
	}

	inline WScene* WSceneManager::LoadScene(const std::wstring& Name)
	{
		if (ActiveScene != nullptr)
		{
			ActiveScene->OnExit();
		}

		std::map<std::wstring, WScene*>::iterator iter =
			Scenes.find(Name);

		if (iter == Scenes.end())
		{
			return nullptr;
		}

		ActiveScene = iter->second;

		ActiveScene->OnEnter();

		return iter->second;
	}
}

