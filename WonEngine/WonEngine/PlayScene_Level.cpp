#include "PlayScene_Level.h"
#include "Transform.h"
#include "SpriteRenderComponent.h"
#include "Player.h"
#include "Input.h"
#include "Scene_LevelManager.h"
#include "WonObject.h"
#include "WTexture.h"

Won::PlayScene_Level::PlayScene_Level()
{
}

Won::PlayScene_Level::~PlayScene_Level()
{
}

void Won::PlayScene_Level::Initialize()
{
	Scene_Level::Initialize();

	Player* Py = InstanceSpawn<Player>(LayerType::BackGround);
	SpriteRenderComponent* SRC = Py->AddComponent<SpriteRenderComponent>();

	WTexture* BackGround = new WTexture();
	BackGround->Load(L"M:/visualstudio/WonEngine/Resource/mountains.png");
	
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
