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

		void SetTileSize(sVector2<float> NewVector) { mSize = NewVector; }
		void SetTexture(class WTexture* NewTexture) { texture = NewTexture; }
		void SetSheetIndex(sVector2<int> NewVector) { mSheetIndex = NewVector; }
		sVector2<float> GetSize() { return mSize; }
		sVector2<int> GetSheetIndex() { return mSheetIndex; }

	private:
		class WTexture* texture;
		sVector2<int> mSheetIndex;
		sVector2<float> mSize;
    };
}

