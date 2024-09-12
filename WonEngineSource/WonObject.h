#pragma once
#include "../WonEngineSource/GameObject.h"
#include "../WonEngineSource/Scene_Level.h"
#include "../WonEngineSource/Scene_LevelManager.h"
#include "../WonEngineSource/WLayer.h"
#include "../WonEngineSource/Transform.h"

namespace Won
{
	template <typename T>
	static T* InstanceSpawn(LayerType Type)
	{
		T* NewObject = new T();
		Transform* TF = NewObject->GetComponent<Transform>();

		Scene_Level* AS = Scene_LevelManager::GetActiveScene();
		WLayer* Layer = AS->GetLayer(Type);
		Layer->AddGameObject(NewObject);

		return NewObject;

	}
	template <typename T>
	static T* InstanceSpawn(LayerType Type, mVector2<float>* Location)
	{
		T* NewObject = new T();
		Transform* TF = NewObject->GetComponent<Transform>();
		TF->SetPos(Location);
		TF->SetName(L"Transform");

		Scene_Level* AS = Scene_LevelManager::GetActiveScene();
		WLayer* Layer = AS->GetLayer(Type);
		Layer->AddGameObject(NewObject);

		return NewObject;
	}
}

