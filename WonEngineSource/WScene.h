#pragma once
#include "Entry.h"

namespace Won
{
	class WScene : public Entry
	{
	public:
		WScene();
		virtual ~WScene();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC NewDC);
		virtual void Destroy();
		virtual void OnEnter();
		virtual void OnExit();
		virtual void EraseGameObject(class WGameObject* NewGameObject);

		void AddGameObject(WGameObject* NewObject, eLayerType Lt); 
		class WLayer* GetLayer(eLayerType Type) { return Layers[(UINT)Type]; }
		std::vector<class WLayer*> GetLayers() { return Layers; }

	private:
		std::vector<class WLayer*> Layers;
	};
}

