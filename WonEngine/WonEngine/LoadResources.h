#pragma once
#include "../WonEngineSource/WResourceManager.h"
#include "../WonEngineSource/WTexture.h"

namespace Won
{
	void LoadResources()
	{
		WResourceManager::Load<WTexture>(L"Ba", L"../Resource/BackGround/Background.bmp");
		WResourceManager::Load<WTexture>(L"Ch", L"../Resource/Character/CharacterAlpha.bmp");
		WResourceManager::Load<WTexture>(L"Ee", L"../Resource/Enemy/Enemy.bmp");
		WResourceManager::Load<WTexture>(L"Hu", L"../Resource/HUD/HUD.png");
		WResourceManager::Load<WTexture>(L"Bl", L"../Resource/Item/Block.png");
		WResourceManager::Load<WTexture>(L"It", L"../Resource/Item/Item.bmp");
		WResourceManager::Load<WTexture>(L"Ob", L"../Resource/Item/Object.bmp");
		WResourceManager::Load<WTexture>(L"Ef", L"../Resource/Effect/Sprite.png");
		//WResourceManager::Load<WTexture>(L"Ti", L"../Resource/TileMap.bmp");
	}
}

