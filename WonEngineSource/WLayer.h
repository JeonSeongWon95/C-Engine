#pragma once
#include "Entry.h"

namespace Won
{
	class WLayer : public Entry
	{
	public:
		WLayer();
		virtual ~WLayer();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC NewDC);

		void SetLayerType(eLayerType NewType) { Type = NewType; }
		void AddGameObject(class GameObject* NewObject);

	private:
		eLayerType Type;
		std::vector<class GameObject*> GameObjects;

	};
}

