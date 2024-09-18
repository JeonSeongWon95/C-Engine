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
		mVector2<float> GetScale() { return mscale; }
		float GetRotation() { return Rotation; }
		void SetComponentPosition(mVector2<float> NewPosition) { ComponentPosition = NewPosition; }
		void SetScale(mVector2<float> NewScale) { mscale = NewScale; }
		void SetRotation(float NewRotation) { Rotation = NewRotation; }

	private:
		mVector2<float> ComponentPosition;
		mVector2<float> mscale;
		float Rotation;
    };
}

