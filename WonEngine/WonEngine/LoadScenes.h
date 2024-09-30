#pragma once
#include "../WonEngineSource/WSceneManager.h"
#include "WPlayScene.h"
#include "WEndScene.h"
#include "WTitleScene.h"
#include "TileScene.h"
#include "ToolScene.h"

namespace Won
{
	void LoadScenes()
	{
		WSceneManager::CreateScene<WPlayScene>(L"PlayLevel");
		WSceneManager::CreateScene<WEndScene>(L"EndLevel");
		WSceneManager::CreateScene<WTitleScene>(L"TitleLevel");
		//WSceneManager::CreateScene<ToolScene>(L"ToolLevel");

		WSceneManager::LoadScene(L"TitleLevel");

	}
}
