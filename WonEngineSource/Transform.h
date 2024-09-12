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

		void SetPos(mVector2<float> NewVector) { ComponentPosition = NewVector; }
		mVector2<float> GetComponentPosition() { return ComponentPosition; }

	private:
		mVector2<float> ComponentPosition;
    };
}

