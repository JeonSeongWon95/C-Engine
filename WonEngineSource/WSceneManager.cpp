#include "WSceneManager.h"
#include "WScene.h"
#include "../WonEngine/WonEngine/DontDestoryScene.h"
#include "WGameObject.h"
#include "WLayer.h"

std::map<std::wstring, Won::WScene*> Won::WSceneManager::Scene_Levels = {};
Won::WScene* Won::WSceneManager::ActiveScene_Level = nullptr;
Won::WScene* Won::WSceneManager::DontDestoryScene_Level = nullptr;

Won::WSceneManager::WSceneManager()
{
}

Won::WSceneManager::~WSceneManager()
{
	for(std::map<std::wstring, Won::WScene*>::iterator iter = Scene_Levels.begin();
		iter != Scene_Levels.end();)
	{
		delete iter->second;
		iter = Scene_Levels.erase(iter);
	}
	
	delete DontDestoryScene_Level;
	Scene_Levels.clear();
}

void Won::WSceneManager::Initialize()
{
	DontDestoryScene_Level = CreateScene_Level<DontDestoryScene>(L"DontDestoryScene");
}

void Won::WSceneManager::Update()
{
	ActiveScene_Level->Update();
	DontDestoryScene_Level->Update();
}

void Won::WSceneManager::LateUpdate()
{
	ActiveScene_Level->LateUpdate();
	DontDestoryScene_Level->LateUpdate();
}

void Won::WSceneManager::Render(HDC NewDC)
{
	ActiveScene_Level->Render(NewDC);
	DontDestoryScene_Level->Render(NewDC);
}

void Won::WSceneManager::Destroy()
{
	ActiveScene_Level->Destroy();
	DontDestoryScene_Level->Destroy();
}

std::vector<Won::WGameObject*> Won::WSceneManager::GetGameObjects(eLayerType NewLayer)
{

	std::vector<Won::WGameObject*> GameObj = ActiveScene_Level->GetLayer(NewLayer)->GetGameObject();
	std::vector<Won::WGameObject*> DontObj = DontDestoryScene_Level->GetLayer(NewLayer)->GetGameObject();

	GameObj.insert(GameObj.end(), DontObj.begin(), DontObj.end());

	return GameObj;
}

