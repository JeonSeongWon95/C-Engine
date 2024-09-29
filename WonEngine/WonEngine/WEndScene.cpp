#include "WEndScene.h"
#include "WTransform.h"
#include "WSpriteRenderComponent.h"
#include "Player.h"
#include "WSceneManager.h"
#include "WonObject.h"
#include "WResourceManager.h"
#include "WTexture.h"
#include "WInput.h"
#include "WTime.h"

Won::WEndScene::WEndScene()
	:mReStartTimer(0)
{
}

Won::WEndScene::~WEndScene()
{
}

void Won::WEndScene::Initialize()
{
	WScene::Initialize();

	Player* BackGround = InstanceSpawn<Player>(eLayerType::BackGround);
	WSpriteRenderComponent* RenderComponent = BackGround->AddComponent<WSpriteRenderComponent>();
	RECT rect = { 259,236, 517,472 };
	RenderComponent->SetTexture(WResourceManager::Find<WTexture>(L"Ti"));
	RenderComponent->SetRect(rect);
	RenderComponent->SetStartPosition(sVector2<float>(0, 0));
	RenderComponent->SetSize(sVector2<float>(3.f, 2.f));
}

void Won::WEndScene::Update()
{
	WScene::Update();

	mReStartTimer += WTime::GetDeltaSeconds();

	if (mReStartTimer > 8)
	{
		mReStartTimer = 0;
		WSceneManager::LoadScene(L"PlayLevel");
	}
}

void Won::WEndScene::LateUpdate()
{
	WScene::LateUpdate();

}

void Won::WEndScene::Render(HDC NewDC)
{
	WScene::Render(NewDC);
}

void Won::WEndScene::OnEnter()
{
}

void Won::WEndScene::OnExit()
{
}
