#include "SpriteRenderComponent.h"
#include "GameObject.h"
#include "Transform.h"
#include "WTexture.h"
#include "WRender.h"

Won::SpriteRenderComponent::SpriteRenderComponent()
	: Component(eComponentType::SpriteRender)
	, texture(nullptr)
	, mSize(1.0f, 1.0f)
	, StartPosition(0.0, 0.0)
	, CharacterRectangle{0, 0, 0, 0}
	, mRGB{0, 0, 0}
{
}

Won::SpriteRenderComponent::~SpriteRenderComponent()
{
}

void Won::SpriteRenderComponent::Initialize()
{
}

void Won::SpriteRenderComponent::Update()
{
}

void Won::SpriteRenderComponent::LateUpdate()
{
}

//void Won::SpriteRenderComponent::Render(HDC NewDC)
//{
//	if (texture == nullptr)
//		assert(false);
//
//	FVector2 vc = GetOwner()->GetComponent<Transform>()->GetComponentPosition();
//	vc = MainCamera->CaluatePostion(vc);
//
//	if(texture->GetTextureType() == WTexture::TextureType::Bmp)
//	{
//		TransparentBlt(NewDC, (int)vc.X, (int)vc.Y, texture->GetWidth(), texture->GetHeight(), texture->GetHDC()
//			, CharacterRectangle.left, CharacterRectangle.right, CharacterRectangle.top,
//			CharacterRectangle.bottom, RGB(mRGB.X, mRGB.Y, mRGB.Z));
//	}
//
//	else if (texture->GetTextureType() == WTexture::TextureType::png)
//	{
//		Gdiplus::Graphics graphics(NewDC);
//		Gdiplus::Rect srcRect(CharacterRectangle.left, CharacterRectangle.right, CharacterRectangle.top, CharacterRectangle.bottom);
//		Gdiplus::Rect desRect(vc.X + StartPosition.X, vc.Y + StartPosition.Y, texture->GetWidth() * mSize.X, 
//			texture->GetHeight() * mSize.Y);
//
//		if (!(mRGB == CVector3::Zero))
//		{
//			Gdiplus::ImageAttributes imgAttr;
//			Gdiplus::Color transparentColor(mRGB.X, mRGB.Y, mRGB.Z);
//			imgAttr.SetColorKey(transparentColor, transparentColor);
//			graphics.DrawImage(texture->GetImage(), desRect, srcRect.X, srcRect.Y, srcRect.Width, srcRect.Height, Gdiplus::UnitPixel, &imgAttr);
//		}
//
//		graphics.DrawImage(texture->GetImage(), desRect, srcRect.X, srcRect.Y, srcRect.Width, srcRect.Height, Gdiplus::UnitPixel);
//	}
//	
//
//}

void Won::SpriteRenderComponent::Render(HDC NewDC)
{
	if (texture == nullptr)
		assert(false);

	mVector2<float> vc = GetOwner()->GetComponent<Transform>()->GetComponentPosition();

	if (MainCamera != nullptr)
	{
		vc = MainCamera->CaluatePostion(vc);
	}

	if (texture->GetTextureType() == WTexture::TextureType::Bmp)
	{
		TransparentBlt(NewDC, static_cast<int>(vc.X), static_cast<int>(vc.Y), static_cast<int>(texture->GetWidth() * mSize.X),
			static_cast<int>(texture->GetHeight() * mSize.Y), texture->GetHDC(),
			static_cast<int>(CharacterRectangle.left), static_cast<int>(CharacterRectangle.top),
			static_cast<int>(CharacterRectangle.right), static_cast<int>(CharacterRectangle.bottom),
			RGB(static_cast<int>(mRGB.X), static_cast<int>(mRGB.Y), static_cast<int>(mRGB.Z)));
	}
	else if (texture->GetTextureType() == WTexture::TextureType::png)
	{
		Gdiplus::Graphics graphics(NewDC);
		Gdiplus::Rect srcRect(static_cast<int>(CharacterRectangle.left), static_cast<int>(CharacterRectangle.top),
			static_cast<int>(CharacterRectangle.right), static_cast<int>(CharacterRectangle.bottom));
		Gdiplus::Rect desRect = { };
		desRect.X = static_cast<int>(vc.X + StartPosition.X);
		desRect.Y = static_cast<int>(vc.Y + StartPosition.Y);

		if(TextureCuttingSize.X == 0 || TextureCuttingSize.Y == 0)
		{
			desRect.Width = static_cast<int>(texture->GetWidth() * mSize.X); 
			desRect.Height = static_cast<int>(texture->GetHeight() * mSize.Y);
		}
		else
		{
			desRect.Width = static_cast<int>(TextureCuttingSize.X * mSize.X);
			desRect.Height = static_cast<int>(TextureCuttingSize.Y * mSize.Y);

		}

		Gdiplus::ImageAttributes imgAttr;

		if (!(mRGB.X == 0 && mRGB.Y == 0 && mRGB.Z == 0))
		{
			Gdiplus::Color transparentColor(static_cast<BYTE>(mRGB.X), static_cast<BYTE>(mRGB.Y), static_cast<BYTE>(mRGB.Z));
			imgAttr.SetColorKey(transparentColor, transparentColor);
			graphics.DrawImage(texture->GetImage(), desRect, srcRect.X, srcRect.Y, srcRect.Width, srcRect.Height,
				Gdiplus::UnitPixel, &imgAttr);
		}
		else
		{
			graphics.DrawImage(texture->GetImage(), desRect, srcRect.X, srcRect.Y, srcRect.Width, srcRect.Height,
				Gdiplus::UnitPixel);
		}
	}
}

void Won::SpriteRenderComponent::SetTextureSize(UINT NewWidth, UINT NewHeight)
{
	if(texture != nullptr)
	{
		TextureCuttingSize.X = NewWidth;
		TextureCuttingSize.Y = NewHeight;
 	}
}
