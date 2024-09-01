#pragma once
#include "Entry.h"

namespace Won
{

	class GameObject;

	class Component : public Entry
	{
	public:
		Component();
		virtual ~Component();


		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC NewDC);

		void SetOwner(GameObject* NewOwner) { Owner = NewOwner; }
		GameObject* GetOwner() { return Owner; }

	private:
		GameObject* Owner;
	};

}
