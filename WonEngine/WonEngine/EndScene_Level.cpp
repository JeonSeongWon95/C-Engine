#include "EndScene_Level.h"
#include "WTransform.h"
#include "WSpriteRenderComponent.h"
#include "Player.h"
#include "WSceneManager.h"
#include "WonObject.h"
#include "WResourceManager.h"
#include "WTexture.h"
#include "WInput.h"
#include "WTime.h"

Won::EndScene_Level::EndScene_Level()
	:mReStartTimer(0)
{
}

Won::EndScene_Level::~EndScene_Level()
{
}

void Won::EndScene_Level::Initialize()
{
	WScene::Initialize();

	Player* BackGround = InstanceSpawn<Player>(eLayerType::BackGround);
	WSpriteRenderComponent* RenderComponent = BackGround->AddComponent<WSpriteRenderComponent>();
	RECT rect = { 530,380,780,617 };
	RenderComponent->SetTexture(WResourceManager::Find<WTexture>(L"Hu"));
	RenderComponent->SetRect(rect);
	RenderComponent->SetStartPosition(sVector2<float>(0, 0));
	RenderComponent->SetSize(sVector2<float>(3.f, 2.f));
}

void Won::EndScene_Level::Update()
{
	WScene::Update();

	mReStartTimer += WTime::GetDeltaSeconds();

	if (mReStartTimer > 8)
	{
		mReStartTimer = 0;
		WSceneManager::LoadScene(L"PlayLevel");
	}
}

void Won::EndScene_Level::LateUpdate()
{
	WScene::LateUpdate();

}

void Won::EndScene_Level::Render(HDC NewDC)
{
	WScene::Render(NewDC);
}

void Won::EndScene_Level::OnEnter()
{
}

void Won::EndScene_Level::OnExit()
{
}
