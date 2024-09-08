#pragma once
#include "WResource.h"

namespace Won
{
    class WTexture :  public WResource
    {
    public:

        enum class TextureType
        {
            Bmp,
            png,
            None
        };

    
        WTexture();
        ~WTexture();

        virtual HRESULT Load(const std::wstring& NewPath) override;
        TextureType GetTextureType() { return TType; }
        Gdiplus::Image* GetImage() { return aImage; }
        HBITMAP GetBitMap() { return aBitmap; }
        HDC GetHDC() { return aDC; }
        UINT GetWidth() { return Width; }
        UINT GetHeight() { return Height; }

    private:
        TextureType TType;
        HBITMAP aBitmap;
        Gdiplus::Image* aImage;
        HDC aDC;

        UINT Width;
        UINT Height;
    };
}

