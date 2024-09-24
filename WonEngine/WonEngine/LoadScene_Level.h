#pragma once
#include "../WonEngineSource/Scene_LevelManager.h"
#include "PlayScene_Level.h"
#include "EndScene_Level.h"
#include "TitleScene_Level.h"
#include "TileScene.h"
#include "ToolScene.h"

namespace Won
{
	void LoadScene_Levels()
	{
		Scene_LevelManager::CreateScene_Level<PlayScene_Level>(L"PlayLevel");
		//Scene_LevelManager::CreateScene_Level<EndScene_Level>(L"EndLevel");
		//Scene_LevelManager::CreateScene_Level<TitleScene_Level>(L"TitleLevel");

		Scene_LevelManager::CreateScene_Level<ToolScene>(L"ToolScene");
		Scene_LevelManager::LoadScene_Level(L"ToolScene");

	}
}
