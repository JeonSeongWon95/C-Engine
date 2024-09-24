#include "Scene_LevelManager.h"
#include "Scene_Level.h"
#include "../WonEngine/WonEngine/\DontDestoryScene.h"

std::map<std::wstring, Won::Scene_Level*> Won::Scene_LevelManager::Scene_Levels = {};
Won::Scene_Level* Won::Scene_LevelManager::ActiveScene_Level = nullptr;

Won::Scene_LevelManager::Scene_LevelManager()
{
}

Won::Scene_LevelManager::~Scene_LevelManager()
{
	for(std::map<std::wstring, Won::Scene_Level*>::iterator iter = Scene_Levels.begin();
		iter != Scene_Levels.end(); ++iter)
	{
		delete iter->second;
		iter = Scene_Levels.erase(iter);
	}
	
	Scene_Levels.clear();
}

void Won::Scene_LevelManager::Initialize()
{
	DontDestoryScene_Level = CreateScene_Level<DontDestoryScene>(L"DontDestoryScene");
}

void Won::Scene_LevelManager::Update()
{
	ActiveScene_Level->Update();
	DontDestoryScene_Level->Update();
}

void Won::Scene_LevelManager::LateUpdate()
{
	ActiveScene_Level->LateUpdate();
	DontDestoryScene_Level->LateUpdate();
}

void Won::Scene_LevelManager::Render(HDC NewDC)
{
	ActiveScene_Level->Render(NewDC);
	DontDestoryScene_Level->Render(NewDC);
}

void Won::Scene_LevelManager::Destroy()
{
	ActiveScene_Level->Destroy();
	DontDestoryScene_Level->Destroy();
}

