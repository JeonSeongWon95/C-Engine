#include "ToolScene.h"
#include "WonObject.h"
#include "TileObject.h"
#include "TileRenderer.h"
#include "ResourceManager.h"
#include "WTexture.h"

Won::ToolScene::ToolScene()
{
}

Won::ToolScene::~ToolScene()
{
}

void Won::ToolScene::Initialize()
{
	TileObject* Object = InstanceSpawn<TileObject>(eLayerType::Tilemap);
	TileRenderer* TileRender = Object->AddComponent<TileRenderer>();
	TileRender->SetTexture(ResourceManager::Find<WTexture>(L"Ti"));	

	Scene_Level::Initialize();
}

void Won::ToolScene::Update()
{
	Scene_Level::Update();
}

void Won::ToolScene::LateUpdate()
{
	Scene_Level::LateUpdate();
}

void Won::ToolScene::Render(HDC NewDC)
{
	Scene_Level::Render(NewDC);

	for (int i = 0; i < 50; ++i)
	{
		MoveToEx(NewDC, 16 * i, 0, NULL);
		LineTo(NewDC, 16 * i, 1000);
	}
	for (int i = 0; i < 50; ++i)
	{
		MoveToEx(NewDC, 0, 16 * i, NULL);
		LineTo(NewDC, 1000, 16 * i);
	}
}

void Won::ToolScene::OnEnter()
{
}

void Won::ToolScene::OnExit()
{
}
