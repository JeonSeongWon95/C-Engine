#pragma once
#include "Component.h"

namespace Won
{
	
	class Transform : public Component
	{
	public:
		Transform();
		~Transform();

		void Initialize() override;
		void Update()  override;
		void LateUpdate()  override;
		void Render(HDC hdc)  override;

		void SetPos(FVector2 NewVector) { ComponentPosition = NewVector; }
		FVector2 GetComponentPosition() { return ComponentPosition; }

	private:
		FVector2 ComponentPosition;
    };
}

