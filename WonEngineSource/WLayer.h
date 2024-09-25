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
		virtual void EraseGameObjcet(class WGameObject* NewGameObject);

		void SetLayerType(eLayerType NewType) { Type = NewType; }
		void AddGameObject(WGameObject* NewObject);
		std::vector<WGameObject*>& GetGameObject() { return GameObjects; }

	private:
		eLayerType Type;
		std::vector<WGameObject*> GameObjects;

	};
}

