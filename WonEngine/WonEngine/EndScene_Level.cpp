#include "EndScene_Level.h"
#include "Transform.h"
#include "SpriteRenderComponent.h"
#include "Player.h"
#include "Input.h"
#include "Scene_LevelManager.h"

Won::EndScene_Level::EndScene_Level()
{
}

Won::EndScene_Level::~EndScene_Level()
{
}

void Won::EndScene_Level::Initialize()
{
	Player* BackGround = new Player;
	Transform* Tf = BackGround->AddComponent<Transform>();
	Tf->SetName(L"TF");
	SpriteRenderComponent* RenderComponent = BackGround->AddComponent<SpriteRenderComponent>();
	RenderComponent->SetName(L"RC");
	RenderComponent->ImageLoad(L"M:/visualstudio/WonEngine/Resource/mountains.png");

	AddGameObject(BackGround, LayerType::BackGround);
}

void Won::EndScene_Level::Update()
{
	Scene_Level::Update();
}

void Won::EndScene_Level::LateUpdate()
{
	Scene_Level::LateUpdate();

	if (Input::GetKeyDown(KeyType::N))
	{
		Scene_LevelManager::LoadScene_Level(L"PlayLevel");
	}
}

void Won::EndScene_Level::Render(HDC NewDC)
{
	Scene_Level::Render(NewDC);
}

void Won::EndScene_Level::OnEnter()
{
}

void Won::EndScene_Level::OnExit()
{
}
