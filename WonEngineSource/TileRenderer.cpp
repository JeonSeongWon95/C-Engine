#include "TileRenderer.h"
#include "Transform.h"
#include "GameObject.h"
#include "WRender.h"
#include "WTexture.h"

Won::TileRenderer::TileRenderer()
	:Component(eComponentType::TileRender)
	,texture(nullptr)
	,mSize(16.0f,16.0f)
	,mSheetIndex(-1,-1)
{
}

Won::TileRenderer::~TileRenderer()
{
}

void Won::TileRenderer::Initialize()
{
}

void Won::TileRenderer::Update()
{
}

void Won::TileRenderer::LateUpdate()
{
}

void Won::TileRenderer::Render(HDC NewDC)
{
	if (texture == nullptr)
		assert(false);

	if (mSheetIndex.X == -1 && mSheetIndex.Y == -1)
		return;

	Transform* Tr = GetOwner()->GetComponent<Transform>();
	mVector2<float> vc = Tr->GetPosition();
	mVector2<float> Sc = Tr->GetScale();

	if (MainCamera != nullptr)
	{
		vc = MainCamera->CaluatePostion(vc);
	}


	if (texture->GetTextureType() == WTexture::TextureType::Bmp)
	{
		if (!texture->IsAlpha())
		{
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
				, RGB(255, 255, 255));
		}
		else
		{
			BLENDFUNCTION func = {};
			func.BlendOp = AC_SRC_OVER;
			func.BlendFlags = 0;
			func.AlphaFormat = AC_SRC_ALPHA;
			func.SourceConstantAlpha = 255;

			AlphaBlend(NewDC
				, static_cast<int>(vc.X)
				, static_cast<int>(vc.Y)
				, static_cast<int>(mSize.X * Sc.X)
				, static_cast<int>(mSize.Y * Sc.Y)
				, texture->GetHDC()
				, static_cast<int>(mSheetIndex.X * mSize.X)
				, static_cast<int>(mSheetIndex.Y * mSize.Y)
				, static_cast<int>(mSize.X)
				, static_cast<int>(mSize.Y)
				, func);
		}
	}
}
