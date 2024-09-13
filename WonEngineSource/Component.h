#pragma once
#include "Entry.h"

namespace Won
{

	class GameObject;

	class Component : public Entry
	{
	public:
		Component(eComponentType NewType);
		virtual ~Component();


		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC NewDC);

		void SetOwner(GameObject* NewOwner) { Owner = NewOwner; }
		GameObject* GetOwner() { return Owner; }
		eComponentType GetType() { return aType; }

	private:
		GameObject* Owner;
		eComponentType aType;
	};

}
