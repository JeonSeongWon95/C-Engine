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
	Transform* CTf = Camera->GetComponent<Transform>();
	CTf->SetPos(mVector2<float>(0, 100));
	Camera->AddComponent<WPlayerScript>();

	BG = InstanceSpawn<Player>(LayerType::BackGround);
	SpriteRenderComponent* BSRC = BG->AddComponent<SpriteRenderComponent>();
	BSRC->SetTexture(ResourceManager::Find<WTexture>(L"Ba"));
	BSRC->SetSize(mVector2<float>(4.0f, 4.0f));
	BSRC->SetStartPosition(mVector2<float>(0, 0));
	RECT NewRect = { 10,33,764,213 };
	BSRC->SetRect(NewRect);
	BSRC->SetTextureSize(NewRect.right - NewRect.left, NewRect.bottom - NewRect.top);
	

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

	if (Input::GetKeyDown(KeyType::A))
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
	TF->SetPos(mVector2<float>(0, 0));
}
