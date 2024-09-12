#pragma once
#include "../WonEngineSource/ResourceManager.h"
#include "../WonEngineSource/WTexture.h"

namespace Won
{
	void LoadResources()
	{
		ResourceManager::Load<WTexture>(L"Ba", L"C:/Work/Visual Studio/Project3/C-Engine/Resource/BackGround/Background.png");
		ResourceManager::Load<WTexture>(L"Ch", L"C:/Work/Visual Studio/Project3/C-Engine/Resource/Character/Character.png");
		ResourceManager::Load<WTexture>(L"Ee", L"C:/Work/Visual Studio/Project3/C-Engine/Resource/Enemy/Enemy.png");
		ResourceManager::Load<WTexture>(L"Hu", L"C:/Work/Visual Studio/Project3/C-Engine/Resource/HUD/HUD.png");
		ResourceManager::Load<WTexture>(L"Bl", L"C:/Work/Visual Studio/Project3/C-Engine/Resource/Item/Block.png");
		ResourceManager::Load<WTexture>(L"Ob", L"C:/Work/Visual Studio/Project3/C-Engine/Resource/Item/Object.png");
		ResourceManager::Load<WTexture>(L"Ti", L"C:/Work/Visual Studio/Project3/C-Engine/Resource/Title/Title.png");
	}
}

