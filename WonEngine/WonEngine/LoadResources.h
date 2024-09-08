#pragma once
#include "../WonEngineSource/ResourceManager.h"
#include "../WonEngineSource/WTexture.h"

namespace Won
{
	void LoadResources()
	{
		ResourceManager::Load<WTexture>(L"Ba", L"M:/visualstudio/WonEngine/Resource/BackGround/Background.png");
		ResourceManager::Load<WTexture>(L"Ch", L"M:/visualstudio/WonEngine/Resource/Character/Character.png");
		ResourceManager::Load<WTexture>(L"Ee", L"M:/visualstudio/WonEngine/Resource/Enemy/Enemy.png");
		ResourceManager::Load<WTexture>(L"Hu", L"M:/visualstudio/WonEngine/Resource/HUD/HUD.png");
		ResourceManager::Load<WTexture>(L"Bl", L"M:/visualstudio/WonEngine/Resource/Item/Block.png");
		ResourceManager::Load<WTexture>(L"Ob", L"M:/visualstudio/WonEngine/Resource/Item/Object.png");
	}
}

