#pragma once
#include "Entry.h"

namespace Won
{
	class Scene_Level : public Entry
	{
	public:
		Scene_Level();
		~Scene_Level();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC NewDC);
		virtual void OnEnter();
		virtual void OnExit();

		void AddGameObject(class GameObject* NewObject, LayerType Lt); 
		class WLayer* GetLayer(LayerType Type) { return Layers[(UINT)Type]; }
		std::vector<class WLayer*> GetLayers() { return Layers; }

	private:
		std::vector<class WLayer*> Layers;
	};
}

