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
		virtual void Destroy();

		void SetLayerType(eLayerType NewType) { Type = NewType; }
		void AddGameObject(class GameObject* NewObject);
		std::vector<class GameObject*>& GetGameObject() { return GameObjects; }

	private:
		eLayerType Type;
		std::vector<class GameObject*> GameObjects;

	};
}

