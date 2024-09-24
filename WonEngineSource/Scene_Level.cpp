#include "Scene_Level.h"
#include "GameObject.h"
#include "WLayer.h"

Won::Scene_Level::Scene_Level()
	:Layers{}
{
	Layers.resize((UINT)eLayerType::Max);

	for(int i = 0; i < Layers.size(); ++i)
	{
		Layers[i] = new WLayer;
	}
}

Won::Scene_Level::~Scene_Level()
{
	for (WLayer* Layer : Layers)
	{
		delete Layer;
	}

	Layers.clear();
}

void Won::Scene_Level::Initialize()
{
	for (WLayer* Layer : Layers)
	{
		if (Layer == nullptr) { continue; }
		Layer->Initialize();
	}
}

void Won::Scene_Level::Update()
{

	for(WLayer* Layer : Layers)
	{
		if (Layer == nullptr) { continue; }
		Layer->Update();
	}
}

void Won::Scene_Level::LateUpdate()
{

	for (WLayer* Layer : Layers)
	{
		if (Layer == nullptr) { continue; }
		Layer->LateUpdate();
	}

}

void Won::Scene_Level::Render(HDC NewDC)
{
	for (WLayer* Layer : Layers)
	{
		if (Layer == nullptr) { continue; }
		Layer->Render(NewDC);
	}
}

void Won::Scene_Level::Destroy()
{
	for (WLayer* Layer : Layers)
	{
		if (Layer == nullptr) { continue; }
		Layer->Destroy();
	}
}

void Won::Scene_Level::OnEnter()
{
}

void Won::Scene_Level::OnExit()
{
}

void Won::Scene_Level::EraseGameObject(GameObject* NewGameObject)
{
	Layers[(UINT)NewGameObject->GetLayerType()]->EraseGameObjcet(NewGameObject);
}

void Won::Scene_Level::AddGameObject(GameObject* NewObject, eLayerType Lt)
{
	Layers[(UINT)Lt]->AddGameObject(NewObject);
}
