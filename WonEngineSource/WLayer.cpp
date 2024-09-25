#include "WLayer.h"
#include "WGameObject.h"

Won::WLayer::WLayer()
	: Type(eLayerType::None)
	, GameObjects{}
{

}

Won::WLayer::~WLayer()
{
	for(WGameObject* WGameObject : GameObjects)
	{
		delete WGameObject;
	}

	GameObjects.clear();
}

void Won::WLayer::Initialize()
{
	for (WGameObject* WGameObject : GameObjects)
	{
		if (WGameObject == nullptr) { continue; }

		WGameObject->Initialize();
	}
}

void Won::WLayer::Update()
{
	for (WGameObject* WGameObject : GameObjects)
	{
		if (WGameObject == nullptr)
			continue;
		if (WGameObject->GetActive() == WGameObject::eState::Pased || WGameObject->GetActive() == WGameObject::eState::Death)
			continue;

		WGameObject->Update();
	}
}

void Won::WLayer::LateUpdate()
{
	for (WGameObject* WGameObject : GameObjects)
	{
		if (WGameObject == nullptr)
			continue;
		if (WGameObject->GetActive() == WGameObject::eState::Pased || WGameObject->GetActive() == WGameObject::eState::Death)
			continue;

		WGameObject->LateUpdate();
	}
}

void Won::WLayer::Render(HDC NewDC)
{

	for (WGameObject* WGameObject : GameObjects)
	{
		if (WGameObject == nullptr) 
			continue; 
		if (WGameObject->GetActive() == WGameObject::eState::Pased || WGameObject->GetActive() == WGameObject::eState::Death)
			continue;

		WGameObject->Render(NewDC);
	}
}

void Won::WLayer::Destroy()
{
	for (std::vector<class WGameObject*>::iterator iter = GameObjects.begin();
		iter != GameObjects.end();)
	{
		if ((*iter)->GetActive() == WGameObject::eState::Death)
		{
			WGameObject* DeleteObj = *(iter);
			iter = GameObjects.erase(iter);
			delete DeleteObj;
			DeleteObj = nullptr;
			continue;
		}

		iter++;
			
	}
}

void Won::WLayer::EraseGameObjcet(WGameObject* NewGameObject)
{
	for (std::vector<class WGameObject*>::iterator iter = GameObjects.begin();
		iter != GameObjects.end(); ++iter)
	{
		if (*iter == NewGameObject)
		{
			iter = GameObjects.erase(iter);
			return;
		}

	}
}

void Won::WLayer::AddGameObject(WGameObject* NewObject)
{
	if (NewObject == nullptr) { return; }
	GameObjects.push_back(NewObject);
}
