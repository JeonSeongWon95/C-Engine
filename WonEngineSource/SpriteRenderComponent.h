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
		void SetSize(mVector2<float> NewSize) { mSize = NewSize; }
		void SetStartPosition(mVector2<float> NewPosition) { StartPosition = NewPosition; }
		void SetRect(RECT NewRECT) { CharacterRectangle = NewRECT; }
		void SetRGB(CVector3 NewRGB) { mRGB = NewRGB; }
		void SetTextureSize(UINT NewWidth, UINT NewHeight);

	private:
		class WTexture* texture;
		mVector2<float> mSize;
		mVector2<float> CuttingSize;
		mVector2<float> StartPosition;
		CVector3 mRGB;
		RECT CharacterRectangle;
		mVector2<UINT> TextureCuttingSize;
		
	};
}

