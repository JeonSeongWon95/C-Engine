#include "TitleScene_Level.h"
#include "Player.h"
#include "WonObject.h"
#include "SpriteRenderComponent.h"
#include "ResourceManager.h"
#include "WTexture.h"
#include "WCamera.h"
#include "Input.h"

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
	//Transform* CameraTransform = Camera->GetComponent<Transform>();
	//CameraTransform->SetPos(FVector2(0, 0));
	//CameraComponent->SetName(L"CC");

	Player* BG = InstanceSpawn<Player>(eLayerType::BackGround);
	SpriteRenderComponent* SRC = BG->AddComponent<SpriteRenderComponent>();
	SRC->SetTexture(ResourceManager::Find<WTexture>(L"Hu"));
	RECT rect = { 0, 120, 258, 300 };
	SRC->SetRect(rect);
	SRC->SetStartPosition(mVector2<float>(0, 0));
	SRC->SetName(L"SRC");

	//Player* Number = InstanceSpawn<Player>(LayerType::Environment);
	//SpriteRenderComponent* SRCS = Number->AddComponent<SpriteRenderComponent>();
	//SRCS->SetTexture(ResourceManager::Find<WTexture>(L"Ti"));
	//RECT rectS = { 25,75,72,80 };
	//SRCS->SetRect(rectS);
	//SRCS->SetStartPosition(mVector2<float>(0, 0));
	////SRCS->SetSize(mVector2<float>(5, 5));
	//SRCS->SetTextureSize(rectS.right - rectS.left, rectS.bottom - rectS.top);
}

void Won::TitleScene_Level::Update()
{
	Scene_Level::Update();

	if (Input::GetKey(KeyType::A))
	{
		Scene_LevelManager::LoadScene_Level(L"EndLevel");
	}
}

void Won::TitleScene_Level::LateUpdate()
{
	Scene_Level::LateUpdate();

}

void Won::TitleScene_Level::Render(HDC NewDC)
{
	Scene_Level::Render(NewDC);
}

void Won::TitleScene_Level::OnEnter()
{
}

void Won::TitleScene_Level::OnExit()
{
}
