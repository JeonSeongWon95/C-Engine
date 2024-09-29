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
		WResourceManager::Load<WTexture>(L"Ti", L"../Resource/HUD/Title.bmp");
		WResourceManager::Load<WTexture>(L"Se", L"../Resource/HUD/Seletors.bmp");
		WResourceManager::Load<WTexture>(L"Ga", L"../Resource/HUD/GameOver.png");
		WResourceManager::Load<WTexture>(L"Bl", L"../Resource/Item/BlockAlpha.bmp");
		WResourceManager::Load<WTexture>(L"It", L"../Resource/Item/ItemAlpha.bmp");
		WResourceManager::Load<WTexture>(L"Ob", L"../Resource/Item/Object.bmp");
		WResourceManager::Load<WTexture>(L"Ef", L"../Resource/Effect/Sprite.png");
		WResourceManager::Load<WTexture>(L"Te", L"../Resource/Tiles.bmp");
	}
}

