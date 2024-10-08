#include "WTexture.h"
#include "WonApplication.h"


extern Won::WonApplication Engine;

Won::WTexture::WTexture()
	: WResource(eResourceType::Texture)
	, TType(TextureType::None)
	, aBitmap(nullptr)
	, aImage(nullptr)
	, aDC(nullptr)
	, Width(0)
	, Height(0)
	, mIsAlpha(false)
{
}

Won::WTexture::~WTexture()
{
	if(aImage)
	{
		delete aImage;
	}
}

HRESULT Won::WTexture::Load(const std::wstring& NewPath)
{
	std::wstring ext = NewPath.substr(NewPath.find_last_of(L".") + 1);

	if (ext == L"bmp")
	{
		TType = TextureType::Bmp;
		aBitmap = (HBITMAP)LoadImageW(nullptr, NewPath.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		if (aBitmap == nullptr)
		{
			return S_FALSE;
		}

		BITMAP info = {};
		GetObject(aBitmap, sizeof(BITMAP), &info);

		Width = info.bmWidth;
		Height = info.bmHeight;
		if(info.bmBitsPixel == 32)
		{
			mIsAlpha = true;
		}

		HDC	NewDC = Engine.GetEngineDC();
		aDC = CreateCompatibleDC(NewDC);
		HBITMAP DeletBitmap = (HBITMAP)SelectObject(aDC, aBitmap);
		DeleteObject(DeletBitmap);
	}
	if (ext == L"png")
	{
		TType = TextureType::png;
		aImage = Gdiplus::Image::FromFile(NewPath.c_str());
		if (aImage == nullptr)
		{
			return S_FALSE;
		}


		Width = aImage->GetWidth();
		Height = aImage->GetHeight();




	}

	return S_OK;
}
