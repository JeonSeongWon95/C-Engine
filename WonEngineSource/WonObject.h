#pragma once
#include "GameObject.h"
#include "Scene_Level.h"
#include "Scene_LevelManager.h"
#include "WLayer.h"
#include "Transform.h"

namespace Won
{
	template <typename T>
	static T* InstanceSpawn(LayerType Type)
	{
		T* NewObject = new T();
		Transform* TF = NewObject->GetComponent<Transform>();
		TF->SetName(L"Transform");

		Scene_Level* AS = Scene_LevelManager::GetActiveScene();
		WLayer* Layer = AS->GetLayer(Type);
		Layer->AddGameObject(NewObject);

		return NewObject;

	}
	template <typename T>
	static T* InstanceSpawn(LayerType Type, FVector2* Location)
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

