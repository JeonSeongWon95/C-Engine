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
	WScene::Update();
}

void Won::DontDestoryScene::LateUpdate()
{
	WScene::LateUpdate();
}

void Won::DontDestoryScene::Render(HDC NewDC)
{
	WScene::Render(NewDC);
}
