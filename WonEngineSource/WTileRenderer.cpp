#include "WTileRenderer.h"
#include "WTransform.h"
#include "WGameObject.h"
#include "WRender.h"
#include "WTexture.h"

Won::WTileRenderer::WTileRenderer()
	:WComponent(eComponentType::TileRender)
	,texture(nullptr)
	,mSize(16.0f,16.0f)
	,mSheetIndex(-1,-1)
{
}

Won::WTileRenderer::~WTileRenderer()
{
}

void Won::WTileRenderer::Initialize()
{
}

void Won::WTileRenderer::Update()
{
}

void Won::WTileRenderer::LateUpdate()
{
}

void Won::WTileRenderer::Render(HDC NewDC)
{
	if (texture == nullptr)
		assert(false);

	if (mSheetIndex.X == -1 && mSheetIndex.Y == -1)
		return;

	WTransform* Tr = GetOwner()->GetComponent<WTransform>();
	sVector2<float> vc = Tr->GetPosition();
	sVector2<float> Sc = Tr->GetScale();

	if (MainCamera != nullptr)
	{
		vc = MainCamera->CaluatePostion(vc);
	}


	if (texture->GetTextureType() == WTexture::TextureType::Bmp)
	{
		//if (!texture->IsAlpha())
		//{
			TransparentBlt(NewDC
				, static_cast<int>(vc.X)
				, static_cast<int>(vc.Y)
				, static_cast<int>(mSize.X * Sc.X)
				, static_cast<int>(mSize.Y * Sc.Y)
				, texture->GetHDC()
				, static_cast<int>(mSheetIndex.X * mSize.X)
				, static_cast<int>(mSheetIndex.Y * mSize.Y)
				, static_cast<int>(mSize.X)
				, static_cast<int>(mSize.Y)
				, RGB(255, 0, 255));
		//}
		//else
		//{
		//	BLENDFUNCTION func = {};
		//	func.BlendOp = AC_SRC_OVER;
		//	func.BlendFlags = 0;
		//	func.AlphaFormat = AC_SRC_ALPHA;
		//	func.SourceConstantAlpha = 255;

		//	AlphaBlend(NewDC
		//		, static_cast<int>(vc.X)
		//		, static_cast<int>(vc.Y)
		//		, static_cast<int>(mSize.X * Sc.X)
		//		, static_cast<int>(mSize.Y * Sc.Y)
		//		, texture->GetHDC()
		//		, static_cast<int>(mSheetIndex.X * mSize.X)
		//		, static_cast<int>(mSheetIndex.Y * mSize.Y + 11)
		//		, static_cast<int>(mSize.X)
		//		, static_cast<int>(mSize.Y)
		//		, func);
		//}
	}
}
