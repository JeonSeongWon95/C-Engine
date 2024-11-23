#include "ItemBlock.h"
#include "WBoxCollider2D.h"
#include "WTexture.h"
#include "WAnimator.h"
#include "WItemBlockScript.h"
#include "WResourceManager.h"

Won::ItemBlock::ItemBlock()
{
}

Won::ItemBlock::~ItemBlock()
{
}

void Won::ItemBlock::Initialize()
{
	WBoxCollider2D* blockCollider = AddComponent<WBoxCollider2D>();
	blockCollider->SetSize(Vector2(50.0f, 50.0f));

	WItemBlockScript* blockScript = AddComponent<WItemBlockScript>();

	WTexture* blockTexture = WResourceManager::Find<WTexture>(L"Bl");
	WAnimator* blockAnimator = AddComponent<WAnimator>();
	blockAnimator->CreateAnimation(L"Idle", blockTexture, Vector2(80, 112), Vector2(16, 16), Vector2(0, 0), 1, 0.1f);
	blockAnimator->CreateAnimation(L"Change", blockTexture, Vector2(144, 112), Vector2(16, 16), Vector2(0, 0), 1, 0.1f);
	blockAnimator->PlayAnimation(L"Change", false);

	WGameObject::Initialize();
}

void Won::ItemBlock::Update()
{
	WGameObject::Update();
}

void Won::ItemBlock::LateUpdate()
{
	WGameObject::LateUpdate();
}

void Won::ItemBlock::Render(HDC NewDC)
{
	WGameObject::Render(NewDC);
}
