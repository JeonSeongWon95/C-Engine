#pragma once
#include "Entry.h"

namespace Won
{

	class WGameObject;

	class WComponent : public Entry
	{
	public:
		WComponent(eComponentType NewType);
		virtual ~WComponent();


		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC NewDC);

		void SetOwner(WGameObject* NewOwner) { Owner = NewOwner; }
		WGameObject* GetOwner() { return Owner; }
		eComponentType GetType() { return aType; }

	private:
		WGameObject* Owner;
		eComponentType aType;
	};

}
