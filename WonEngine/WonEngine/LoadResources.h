#pragma once
#include "../WonEngineSource/ResourceManager.h"
#include "../WonEngineSource/WTexture.h"

namespace Won
{
	void LoadResources()
	{
		ResourceManager::Load<WTexture>(L"Ba", L"../Resource/BackGround/Background.bmp");
		ResourceManager::Load<WTexture>(L"Ch", L"../Resource/Character/CharacterAlpha.bmp");
		ResourceManager::Load<WTexture>(L"Ee", L"../Resource/Enemy/Enemy.bmp");
		ResourceManager::Load<WTexture>(L"Hu", L"../Resource/HUD/HUD.png");
		ResourceManager::Load<WTexture>(L"Bl", L"../Resource/Item/Block.png");
		ResourceManager::Load<WTexture>(L"Ob", L"../Resource/Item/Object.bmp");
		ResourceManager::Load<WTexture>(L"It", L"../Resource/Item/Item.bmp");
		ResourceManager::Load<WTexture>(L"Ef", L"../Resource/Effect/Sprite.png");
	}
}

