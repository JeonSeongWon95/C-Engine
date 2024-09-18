#include "EndScene_Level.h"
#include "Transform.h"
#include "SpriteRenderComponent.h"
#include "Player.h"
#include "Scene_LevelManager.h"
#include "WonObject.h"
#include "ResourceManager.h"
#include "WTexture.h"
#include "Input.h"

Won::EndScene_Level::EndScene_Level()
{
}

Won::EndScene_Level::~EndScene_Level()
{
}

void Won::EndScene_Level::Initialize()
{
	Scene_Level::Initialize();

	Player* BackGround = InstanceSpawn<Player>(eLayerType::BackGround);
	SpriteRenderComponent* RenderComponent = BackGround->AddComponent<SpriteRenderComponent>();
	RECT rect = { 530,380,780,617 };
	RenderComponent->SetTexture(ResourceManager::Find<WTexture>(L"Hu"));
	RenderComponent->SetRect(rect);
	RenderComponent->SetStartPosition(mVector2<float>(0, 0));
	RenderComponent->SetSize(mVector2<float>(3.f, 2.f));
}

void Won::EndScene_Level::Update()
{
	Scene_Level::Update();
}

void Won::EndScene_Level::LateUpdate()
{
	Scene_Level::LateUpdate();

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
