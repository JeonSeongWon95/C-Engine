#include "WLayer.h"
#include "GameObject.h"

Won::WLayer::WLayer()
{

}

Won::WLayer::~WLayer()
{
	for(GameObject* GameObject : GameObjects)
	{
		delete GameObject;
	}

	GameObjects.clear();
}

void Won::WLayer::Initialize()
{
	for (GameObject* GameObject : GameObjects)
	{
		if (GameObject == nullptr) { continue; }

		GameObject->Initialize();
	}
}

void Won::WLayer::Update()
{
	for (GameObject* GameObject : GameObjects)
	{
		if (GameObject == nullptr) { continue; }
		GameObject->Update();
	}
}

void Won::WLayer::LateUpdate()
{
	for (GameObject* GameObject : GameObjects)
	{
		if (GameObject == nullptr) { continue; }
		GameObject->LateUpdate();
	}
}

void Won::WLayer::Render(HDC NewDC)
{

	for (GameObject* GameObject : GameObjects)
	{
		if (GameObject == nullptr) 
		{ 
			continue; 
		}

		GameObject->Render(NewDC);
	}
}

void Won::WLayer::AddGameObject(GameObject* NewObject)
{
	if (NewObject == nullptr) { return; }
	GameObjects.push_back(NewObject);
}
