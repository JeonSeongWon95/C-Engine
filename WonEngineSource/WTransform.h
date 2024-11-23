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

		void SetPos(Vector2 NewVector) { Position = NewVector; }
		Vector2 GetPosition() { return Position; }
		Vector2 GetScale() { return mscale; }
		float GetRotation() { return Rotation; }
		void SetScale(Vector2 NewScale) { mscale = NewScale; }
		void SetRotation(float NewRotation) { Rotation = NewRotation; }

	private:
		Vector2 Position;
		Vector2 mscale;
		float Rotation;
    };
}

