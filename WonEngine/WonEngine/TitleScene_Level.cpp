#include "TitleScene_Level.h"
#include "Player.h"
#include "WonObject.h"
#include "WSpriteRenderComponent.h"
#include "WResourceManager.h"
#include "WTexture.h"
#include "WCamera.h"
#include "WInput.h"

Won::TitleScene_Level::TitleScene_Level()
{
}

Won::TitleScene_Level::~TitleScene_Level()
{
}

void Won::TitleScene_Level::Initialize()
{
	//GameObject* Camera = InstanceSpawn<GameObject>(LayerType::None);
	//WCamera* CameraComponent = Camera->AddComponent<WCamera>();
	//WTransform* CameraTransform = Camera->GetComponent<WTransform>();
	//CameraTransform->SetPos(FVector2(0, 0));
	//CameraComponent->SetName(L"CC");

	Player* BG = InstanceSpawn<Player>(eLayerType::BackGround);
	WSpriteRenderComponent* SRC = BG->AddComponent<WSpriteRenderComponent>();
	SRC->SetTexture(WResourceManager::Find<WTexture>(L"Hu"));
	RECT rect = { 0, 120, 258, 300 };
	SRC->SetRect(rect);
	SRC->SetStartPosition(sVector2<float>(0, 0));
	SRC->SetName(L"SRC");

	//Player* Number = InstanceSpawn<Player>(LayerType::Environment);
	//WSpriteRenderComponent* SRCS = Number->AddComponent<WSpriteRenderComponent>();
	//SRCS->SetTexture(WResourceManager::Find<WTexture>(L"Ti"));
	//RECT rectS = { 25,75,72,80 };
	//SRCS->SetRect(rectS);
	//SRCS->SetStartPosition(mVector2<float>(0, 0));
	////SRCS->SetSize(mVector2<float>(5, 5));
	//SRCS->SetTextureSize(rectS.right - rectS.left, rectS.bottom - rectS.top);
}

void Won::TitleScene_Level::Update()
{
	WScene::Update();

	if (WInput::GetKey(KeyType::A))
	{
		WSceneManager::LoadScene_Level(L"EndLevel");
	}
}

void Won::TitleScene_Level::LateUpdate()
{
	WScene::LateUpdate();

}

void Won::TitleScene_Level::Render(HDC NewDC)
{
	WScene::Render(NewDC);
}

void Won::TitleScene_Level::OnEnter()
{
}

void Won::TitleScene_Level::OnExit()
{
}
