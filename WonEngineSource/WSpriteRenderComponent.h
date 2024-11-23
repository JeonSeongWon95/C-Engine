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
		void SetSize(Vector2 NewSize) { mSize = NewSize; }
		void SetStartPosition(Vector2 NewPosition) { StartPosition = NewPosition; }
		void SetRect(RECT NewRECT) { CharacterRectangle = NewRECT; }
		void SetRemoveRGB(Vector3 NewRGB) { RemoveRGB = NewRGB; }
		void SetTextureSize(int NewWidth, int NewHeight);

	private:
		class WTexture* texture;
		Vector2 mSize;
		Vector2 CuttingSize;
		Vector2 StartPosition;
		Vector3 RemoveRGB;
		RECT CharacterRectangle;
		Vector2 TextureCuttingSize;
		
	};
}

