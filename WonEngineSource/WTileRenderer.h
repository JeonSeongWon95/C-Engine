#pragma once
#include "WComponent.h"


namespace Won
{
    class WTileRenderer : public WComponent
    {
	public:
		WTileRenderer();
		~WTileRenderer();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC NewDC) override;

		void SetTileSize(Vector2 NewVector) { mSize = NewVector; }
		void SetTexture(class WTexture* NewTexture) { texture = NewTexture; }
		void SetSheetIndex(Vector2 NewVector) { mSheetIndex = NewVector; }
		Vector2 GetSize() { return mSize; }
		Vector2 GetSheetIndex() { return mSheetIndex; }

	private:
		class WTexture* texture;
		Vector2 mSheetIndex;
		Vector2 mSize;
    };
}

