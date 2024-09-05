#pragma once
#include "WResource.h"

namespace Won
{
    class WTexture :  public WResource
    {
        enum class TextureType
        {
            Bmp,
            png,
            None
        };

    public:
        WTexture();
        ~WTexture();

        virtual HRESULT Load(const std::wstring& NewPath) override;

    private:
        TextureType TType;
        HBITMAP aBitmap;
        Gdiplus::Image* aImage;
        HDC aDC;

        UINT Width;
        UINT Height;
    };
}

