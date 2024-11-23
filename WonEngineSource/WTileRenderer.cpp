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

	if (mSheetIndex.x == -1 && mSheetIndex.y == -1)
		return;

	WTransform* Tr = GetOwner()->GetComponent<WTransform>();
	Vector2 vc = Tr->GetPosition();
	Vector2 Sc = Tr->GetScale();

	if (MainCamera != nullptr)
	{
		vc = MainCamera->CaluatePostion(vc);
	}


	if (texture->GetTextureType() == WTexture::TextureType::Bmp)
	{

		TransparentBlt(NewDC
			, static_cast<int>(vc.x)
			, static_cast<int>(vc.y)
			, static_cast<int>(mSize.x * Sc.x)
			, static_cast<int>(mSize.y * Sc.y)
			, texture->GetHDC()
			, static_cast<int>(mSheetIndex.x * mSize.x)
			, static_cast<int>(mSheetIndex.y * mSize.y)
			, static_cast<int>(mSize.x)
			, static_cast<int>(mSize.y)
			, RGB(255, 0, 255));

	}

}
