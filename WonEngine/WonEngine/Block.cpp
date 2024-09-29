#include "Block.h"
#include "WBoxCollider2D.h"
#include "WBlockScript.h"
#include "WAnimator.h"
#include "WResourceManager.h"
#include "WTexture.h"

Won::Block::Block()
{
}

Won::Block::~Block()
{
}

void Won::Block::Initialize()
{
	WBoxCollider2D* blockCollider = AddComponent<WBoxCollider2D>();
	blockCollider->SetSize(sVector2<float>(50.0f, 50.0f));

	WBlockScript* blockScript = AddComponent<WBlockScript>();

	WTexture* blockTexture = WResourceManager::Find<WTexture>(L"Bl");
	WAnimator* blockAnimator = AddComponent<WAnimator>();
	blockAnimator->CreateAnimation(L"Idle", blockTexture, sVector2<float>(272, 112), sVector2<float>(16, 16), sVector2<float>(0, 0), 1, 0.1f);
	blockAnimator->PlayAnimation(L"Idle", false);

	WGameObject::Initialize();
}

void Won::Block::Update()
{
	WGameObject::Update();
}

void Won::Block::LateUpdate()
{
	WGameObject::LateUpdate();
}

void Won::Block::Render(HDC NewDC)
{
	WGameObject::Render(NewDC);
}
