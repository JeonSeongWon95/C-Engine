#pragma once
#include "../WonEngineSource/WGameObject.h"
#include "../WonEngineSource/WScene.h"
#include "../WonEngineSource/WSceneManager.h"
#include "../WonEngineSource/WLayer.h"
#include "../WonEngineSource/WTransform.h"

namespace Won
{
	template <typename T>
	static T* InstanceSpawn(eLayerType Type)
	{
		T* NewObject = new T();
		WTransform* TF = NewObject->GetComponent<WTransform>();
		NewObject->SetLayerType(Type);
		WScene* AS = WSceneManager::GetActiveScene();
		WLayer* Layer = AS->GetLayer(Type);
		Layer->AddGameObject(NewObject);

		return NewObject;

	}
	template <typename T>
	static T* InstanceSpawn(eLayerType Type,Vector2 Location)
	{
		T* NewObject = new T();
		WTransform* TF = NewObject->GetComponent<WTransform>();
		TF->SetPos(Location);
		TF->SetName(L"WTransform");
		NewObject->SetLayerType(Type);
		WScene* AS = WSceneManager::GetActiveScene();
		WLayer* Layer = AS->GetLayer(Type);
		Layer->AddGameObject(NewObject);

		return NewObject;
	}

	static void Destroy(WGameObject* NewGameObject)
	{
		NewGameObject->DoDeath();
	}

	static void DestoryOnLoadScene(WGameObject* NewGameObject)
	{
		eLayerType GLayerType = NewGameObject->GetLayerType();
		WScene* AS = WSceneManager::GetActiveScene();
		AS->EraseGameObject(NewGameObject);
		
		WScene* DD = WSceneManager::GetDontDestoryOnScene();
		DD->AddGameObject(NewGameObject, NewGameObject->GetLayerType());

	}
}

