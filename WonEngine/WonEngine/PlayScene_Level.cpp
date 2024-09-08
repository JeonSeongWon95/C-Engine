#include "PlayScene_Level.h"
#include "Transform.h"
#include "SpriteRenderComponent.h"
#include "Player.h"
#include "Input.h"
#include "Scene_LevelManager.h"
#include "WonObject.h"
#include "WTexture.h"
#include "ResourceManager.h"
#include "WPlayerScript.h"
#include "WCamera.h"
#include "WRender.h"

Won::PlayScene_Level::PlayScene_Level()
{
}

Won::PlayScene_Level::~PlayScene_Level()
{
}
 
void Won::PlayScene_Level::Initialize()
{
	Scene_Level::Initialize();

	GameObject* Camera = InstanceSpawn<GameObject>(LayerType::None);
	WCamera* CameraComponent = Camera->AddComponent<WCamera>();
	MainCamera = CameraComponent;

	//Camera->AddComponent<WPlayerScript>();

	Player* Bg = InstanceSpawn<Player>(LayerType::BackGround);
	SpriteRenderComponent* BSRC = Bg->AddComponent<SpriteRenderComponent>();
	BSRC->SetTexture(ResourceManager::Find<WTexture>(L"Ba"));
	BSRC->SetSize(FVector2(3.0f, 3.0f));
	BSRC->SetStartPosition(FVector2(0, 0));
	RECT NewRect = { 0, 0, 319, 254 };
	BSRC->SetRect(NewRect);

	Player* Ch = InstanceSpawn<Player>(LayerType::Character);
	SpriteRenderComponent* CSRC = Ch->AddComponent<SpriteRenderComponent>();
	CSRC->SetTexture(ResourceManager::Find<WTexture>(L"Ch"));
	Ch->AddComponent<WPlayerScript>();
}

void Won::PlayScene_Level::Update()
{
	Scene_Level::Update();
}

void Won::PlayScene_Level::LateUpdate()
{
	Scene_Level::LateUpdate();

	if (Input::GetKeyDown(KeyType::N))
	{
		Scene_LevelManager::LoadScene_Level(L"EndLevel");
	}
}

void Won::PlayScene_Level::Render(HDC NewDC)
{
	Scene_Level::Render(NewDC);
}

void Won::PlayScene_Level::OnEnter()
{

}

void Won::PlayScene_Level::OnExit()
{
	Transform* TF = BG->GetComponent<Transform>();
	TF->SetPos(FVector2(0, 0));
}
