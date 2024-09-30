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

	Player* BG = InstanceSpawn<Player>(eLayerType::BackGround);
	WSpriteRenderComponent* SRC = BG->AddComponent<WSpriteRenderComponent>();
	SRC->SetTexture(WResourceManager::Find<WTexture>(L"Ti"));
	RECT rect = { 260, 250, 260, 200 };
	SRC->SetRect(rect);
	SRC->SetStartPosition(sVector2<float>(0, 0));
	SRC->SetName(L"SRC");
	SRC->SetSize(sVector2<float>(1.0, 1.5));
}

void Won::WEndScene::Update()
{
	WScene::Update();

	mReStartTimer += WTime::GetDeltaSeconds();

	if (mReStartTimer > 10)
	{
		mReStartTimer = 0;
		WSceneManager::LoadScene(L"TitleLevel");
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
