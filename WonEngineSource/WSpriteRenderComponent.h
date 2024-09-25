#pragma once
#include "WComponent.h"


namespace Won
{
	class WSpriteRenderComponent : public WComponent
	{
	public:
		WSpriteRenderComponent();
		~WSpriteRenderComponent();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC NewDC) override;

		void SetTexture(class WTexture* NewTexture) { texture = NewTexture; }
		void SetSize(sVector2<float> NewSize) { mSize = NewSize; }
		void SetStartPosition(sVector2<float> NewPosition) { StartPosition = NewPosition; }
		void SetRect(RECT NewRECT) { CharacterRectangle = NewRECT; }
		void SetRemoveRGB(sVector3<int> NewRGB) { RemoveRGB = NewRGB; }
		void SetTextureSize(UINT NewWidth, UINT NewHeight);

	private:
		class WTexture* texture;
		sVector2<float> mSize;
		sVector2<float> CuttingSize;
		sVector2<float> StartPosition;
		sVector3<int> RemoveRGB;
		RECT CharacterRectangle;
		sVector2<UINT> TextureCuttingSize;
		
	};
}

