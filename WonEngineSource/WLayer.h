#pragma once
#include "Entry.h"

namespace Won
{
	class WLayer : public Entry
	{
	public:
		WLayer();
		~WLayer();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC NewDC);

		void SetLayerType(LayerType NewType) { Type = NewType; }
		void AddGameObject(class GameObject* NewObject);

	private:
		LayerType Type;
		std::vector<class GameObject*> GameObjects;

	};
}

