#pragma once
#include "WComponent.h"

namespace Won
{
	
	class WTransform : public WComponent
	{
	public:
		WTransform();
		~WTransform();

		void Initialize() override;
		void Update()  override;
		void LateUpdate()  override;
		void Render(HDC hdc)  override;

		void SetPos(sVector2<float> NewVector) { Position = NewVector; }
		sVector2<float> GetPosition() { return Position; }
		sVector2<float> GetScale() { return mscale; }
		float GetRotation() { return Rotation; }
		void SetScale(sVector2<float> NewScale) { mscale = NewScale; }
		void SetRotation(float NewRotation) { Rotation = NewRotation; }

	private:
		sVector2<float> Position;
		sVector2<float> mscale;
		float Rotation;
    };
}

