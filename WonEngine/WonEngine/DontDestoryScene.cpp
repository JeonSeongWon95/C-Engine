#include "DontDestoryScene.h"

Won::DontDestoryScene::DontDestoryScene()
{
}

Won::DontDestoryScene::~DontDestoryScene()
{
}

void Won::DontDestoryScene::Initialize()
{
}

void Won::DontDestoryScene::Update()
{
	Scene_Level::Update();
}

void Won::DontDestoryScene::LateUpdate()
{
	Scene_Level::LateUpdate();
}

void Won::DontDestoryScene::Render(HDC NewDC)
{
	Scene_Level::Render(NewDC);
}
