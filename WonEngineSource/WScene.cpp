#include "WScene.h"
#include "WGameObject.h"
#include "WLayer.h"

Won::WScene::WScene()
	:Layers{}
{
	Layers.resize((UINT)eLayerType::Max);

	for(int i = 0; i < Layers.size(); ++i)
	{
		Layers[i] = new WLayer;
	}
}

Won::WScene::~WScene()
{
	for (WLayer* Layer : Layers)
	{
		delete Layer;
	}

	Layers.clear();
}

void Won::WScene::Initialize()
{
	for (WLayer* Layer : Layers)
	{
		if (Layer == nullptr) { continue; }
		Layer->Initialize();
	}
}

void Won::WScene::Update()
{

	for(WLayer* Layer : Layers)
	{
		if (Layer == nullptr) { continue; }
		Layer->Update();
	}
}

void Won::WScene::LateUpdate()
{

	for (WLayer* Layer : Layers)
	{
		if (Layer == nullptr) { continue; }
		Layer->LateUpdate();
	}

}

void Won::WScene::Render(HDC NewDC)
{
	for (WLayer* Layer : Layers)
	{
		if (Layer == nullptr) { continue; }
		Layer->Render(NewDC);
	}
}

void Won::WScene::Destroy()
{
	for (WLayer* Layer : Layers)
	{
		if (Layer == nullptr) { continue; }
		Layer->Destroy();
	}
}

void Won::WScene::OnEnter()
{
	
}

void Won::WScene::OnExit()
{
	
}

void Won::WScene::EraseGameObject(WGameObject* NewGameObject)
{
	Layers[(UINT)NewGameObject->GetLayerType()]->EraseGameObjcet(NewGameObject);
}

void Won::WScene::AddGameObject(WGameObject* NewObject, eLayerType Lt)
{
	Layers[(UINT)Lt]->AddGameObject(NewObject);
}
