#include "WTitleScene.h"
#include "Player.h"
#include "WonObject.h"
#include "WSpriteRenderComponent.h"
#include "WResourceManager.h"
#include "WTexture.h"
#include "WCamera.h"
#include "WInput.h"
#include "WUIManager.h"
#include "Player.h"
#include "WSelectScript.h"
#include "WAnimator.h"

Won::WTitleScene::WTitleScene()
{
}

Won::WTitleScene::~WTitleScene()
{
}

void Won::WTitleScene::Initialize()
{
	Player* BG = InstanceSpawn<Player>(eLayerType::BackGround);
	WSpriteRenderComponent* SRC = BG->AddComponent<WSpriteRenderComponent>();
	SRC->SetTexture(WResourceManager::Find<WTexture>(L"Ti"));
	RECT rect = { 0, 10, 258, 236 };
	SRC->SetRect(rect);
	SRC->SetStartPosition(Vector2(0, 0));
	SRC->SetName(L"SRC");
	SRC->SetSize(Vector2(1.0, 1.5));

	Player* Selector = InstanceSpawn<Player>(eLayerType::Player);
	WTransform* SelectorTransform = Selector->GetComponent<WTransform>();
	SelectorTransform->SetScale(Vector2(3.0f, 3.0f));

	WSelectScript* MonsterScript = Selector->AddComponent<WSelectScript>();
	WAnimator* SelectorAnimator = Selector->AddComponent<WAnimator>();

	WTexture* blockTexture = WResourceManager::Find<WTexture>(L"Se");
	SelectorAnimator->CreateAnimation(L"Idle", blockTexture, Vector2(518, 266), Vector2(10, 8), Vector2(0, 0), 1, 0.1f);
	SelectorAnimator->PlayAnimation(L"Idle", false);
}

void Won::WTitleScene::Update()
{
	WScene::Update();

	if (WInput::GetKey(KeyType::ENTER))
	{
		WSceneManager::LoadScene(L"PlayLevel");
	}
}

void Won::WTitleScene::LateUpdate()
{
	WScene::LateUpdate();

}

void Won::WTitleScene::Render(HDC NewDC)
{
	WScene::Render(NewDC);
}

void Won::WTitleScene::OnEnter()
{

}

void Won::WTitleScene::OnExit()
{
	
}
