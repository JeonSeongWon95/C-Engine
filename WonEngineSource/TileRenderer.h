#pragma once
#include "Component.h"


namespace Won
{
    class TileRenderer : public Component
    {
	public:
		TileRenderer();
		~TileRenderer();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC NewDC) override;

		void SetTileSize(mVector2<float> NewVector) { mSize = NewVector; }
		void SetTexture(class WTexture* NewTexture) { texture = NewTexture; }
		void SetSheetIndex(mVector2<int> NewVector) { mSheetIndex = NewVector; }
		mVector2<float> GetSize() { return mSize; }
		mVector2<int> GetSheetIndex() { return mSheetIndex; }

	private:
		class WTexture* texture;
		mVector2<int> mSheetIndex;
		mVector2<float> mSize;
    };
}

