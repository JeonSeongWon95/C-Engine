#include "Scene_LevelManager.h"
#include "Scene_Level.h"

std::map<std::wstring, Won::Scene_Level*> Won::Scene_LevelManager::Scene_Levels = {};
Won::Scene_Level* Won::Scene_LevelManager::ActiveScene_Level = nullptr;

Won::Scene_LevelManager::Scene_LevelManager()
{
}

Won::Scene_LevelManager::~Scene_LevelManager()
{

}

void Won::Scene_LevelManager::Initialize()
{

}

void Won::Scene_LevelManager::Update()
{
	ActiveScene_Level->Update();
}

void Won::Scene_LevelManager::LateUpdate()
{
	ActiveScene_Level->LateUpdate();
}

void Won::Scene_LevelManager::Render(HDC NewDC)
{
	ActiveScene_Level->Render(NewDC);
}
