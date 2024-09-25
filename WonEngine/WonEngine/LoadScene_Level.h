#pragma once
#include "../WonEngineSource/WSceneManager.h"
#include "PlayScene_Level.h"
#include "EndScene_Level.h"
#include "TitleScene_Level.h"
#include "TileScene.h"
#include "ToolScene.h"

namespace Won
{
	void LoadScene_Levels()
	{
		WSceneManager::CreateScene_Level<PlayScene_Level>(L"PlayLevel");
		//WSceneManager::CreateScene_Level<EndScene_Level>(L"EndLevel");
		//WSceneManager::CreateScene_Level<TitleScene_Level>(L"TitleLevel");

		WSceneManager::CreateScene_Level<ToolScene>(L"ToolScene");
		WSceneManager::LoadScene_Level(L"PlayLevel");

	}
}
