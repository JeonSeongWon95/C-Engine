#include "WLayer.h"
#include "GameObject.h"

Won::WLayer::WLayer()
	: Type(eLayerType::None)
	, GameObjects{}
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
		if (GameObject == nullptr)
			continue;
		if (GameObject->GetActive() == GameObject::eState::Pased || GameObject->GetActive() == GameObject::eState::Death)
			continue;

		GameObject->Update();
	}
}

void Won::WLayer::LateUpdate()
{
	for (GameObject* GameObject : GameObjects)
	{
		if (GameObject == nullptr)
			continue;
		if (GameObject->GetActive() == GameObject::eState::Pased || GameObject->GetActive() == GameObject::eState::Death)
			continue;

		GameObject->LateUpdate();
	}
}

void Won::WLayer::Render(HDC NewDC)
{

	for (GameObject* GameObject : GameObjects)
	{
		if (GameObject == nullptr) 
			continue; 
		if (GameObject->GetActive() == GameObject::eState::Pased || GameObject->GetActive() == GameObject::eState::Death)
			continue;

		GameObject->Render(NewDC);
	}
}

void Won::WLayer::Destroy()
{
	for (std::vector<class GameObject*>::iterator iter = GameObjects.begin();
		iter != GameObjects.end();)
	{
		if ((*iter)->GetActive() == GameObject::eState::Death)
		{
			GameObject* DeleteObj = *(iter);
			iter = GameObjects.erase(iter);
			delete DeleteObj;
			DeleteObj = nullptr;
			continue;
		}

		iter++;
			
	}
}

void Won::WLayer::EraseGameObjcet(GameObject* NewGameObject)
{
	for (std::vector<class GameObject*>::iterator iter = GameObjects.begin();
		iter != GameObjects.end(); ++iter)
	{
		if (*iter == NewGameObject)
		{
			iter = GameObjects.erase(iter);
			return;
		}

	}
}

void Won::WLayer::AddGameObject(GameObject* NewObject)
{
	if (NewObject == nullptr) { return; }
	GameObjects.push_back(NewObject);
}
