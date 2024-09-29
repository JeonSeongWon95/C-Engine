#include "Coin.h"
#include "WBoxCollider2D.h"
#include "WTexture.h"
#include "WAnimator.h"
#include "WResourceManager.h"
#include "WCoinScript.h"

Won::Coin::Coin()
{
}

Won::Coin::~Coin()
{
}

void Won::Coin::Initialize()
{
	WBoxCollider2D* CoinCollider = AddComponent<WBoxCollider2D>();
	CoinCollider->SetSize(sVector2<float>(50.0f, 50.0f));

	WCoinScript* CoinScript = AddComponent<WCoinScript>();

	WTexture* CoinTexture = WResourceManager::Find<WTexture>(L"Te");
	WAnimator* CoinAnimator = AddComponent<WAnimator>();
	CoinAnimator->CreateAnimation(L"Idle", CoinTexture, sVector2<float>(384, 16), sVector2<float>(16, 16), sVector2<float>(0, 0), 1, 0.1f);
	CoinAnimator->PlayAnimation(L"Idle", false);

	WGameObject::Initialize();
}

void Won::Coin::Update()
{
	WGameObject::Update();
}

void Won::Coin::LateUpdate()
{
	WGameObject::LateUpdate();
}

void Won::Coin::Render(HDC NewDC)
{
	WGameObject::Render(NewDC);
}
