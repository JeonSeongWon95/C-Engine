#pragma once
#include "Component.h"


namespace Won
{
	class SpriteRenderComponent : public Component
	{
	public:
		SpriteRenderComponent();
		~SpriteRenderComponent();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC NewDC) override;

		void SetTexture(class WTexture* NewTexture) { texture = NewTexture; }
		void SetSize(FVector2 NewSize) { mSize = NewSize; }
		void SetStartPosition(FVector2 NewPosition) { StartPosition = NewPosition; }
		void SetRect(RECT NewRECT) { CharacterRectangle = NewRECT; }
		void SetRGB(CVector3 NewRGB) { mRGB = NewRGB; }

	private:
		class WTexture* texture;
		FVector2 mSize;
		FVector2 StartPosition;
		CVector3 mRGB;
		RECT CharacterRectangle;
		
	};
}

