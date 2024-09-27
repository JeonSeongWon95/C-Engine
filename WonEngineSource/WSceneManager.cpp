#include "WSceneManager.h"
#include "WScene.h"
#include "../WonEngine/WonEngine/WDontDestoryScene.h"
#include "WGameObject.h"
#include "WLayer.h"

std::map<std::wstring, Won::WScene*> Won::WSceneManager::Scenes = {};
Won::WScene* Won::WSceneManager::ActiveScene = nullptr;
Won::WScene* Won::WSceneManager::DontDestoryScene = nullptr;

void Won::WSceneManager::Initialize()
{
	DontDestoryScene = CreateScene<WDontDestoryScene>(L"DontDestoryScene");
}

void Won::WSceneManager::Update()
{
	ActiveScene->Update();
	DontDestoryScene->Update();
}

void Won::WSceneManager::LateUpdate()
{
	ActiveScene->LateUpdate();
	DontDestoryScene->LateUpdate();
}

void Won::WSceneManager::Render(HDC NewDC)
{
	ActiveScene->Render(NewDC);
	DontDestoryScene->Render(NewDC);
}

void Won::WSceneManager::Destroy()
{
	ActiveScene->Destroy();
	DontDestoryScene->Destroy();
}

void Won::WSceneManager::Release()
{
	for (auto& iter : Scenes)
	{
		delete iter.second;
		iter.second = nullptr;
	}
}

std::vector<Won::WGameObject*> Won::WSceneManager::GetGameObjects(eLayerType NewLayer)
{

	std::vector<Won::WGameObject*> GameObj = ActiveScene->GetLayer(NewLayer)->GetGameObject();
	std::vector<Won::WGameObject*> DontObj = DontDestoryScene->GetLayer(NewLayer)->GetGameObject();

	GameObj.insert(GameObj.end(), DontObj.begin(), DontObj.end());

	return GameObj;
}

