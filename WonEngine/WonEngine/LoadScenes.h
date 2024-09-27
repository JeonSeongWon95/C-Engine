#pragma once
#include "../WonEngineSource/WSceneManager.h"
#include "PlayScene_Level.h"
#include "EndScene_Level.h"
#include "WTitleScene.h"
#include "TileScene.h"
#include "ToolScene.h"

namespace Won
{
	void LoadScenes()
	{
		WSceneManager::CreateScene<PlayScene_Level>(L"PlayLevel");
		//WSceneManager::CreateScene<EndScene_Level>(L"EndLevel");
		WSceneManager::CreateScene<WTitleScene>(L"TitleLevel");
		//WSceneManager::CreateScene<ToolScene>(L"ToolScene");

		WSceneManager::LoadScene(L"TitleLevel");

	}
}
