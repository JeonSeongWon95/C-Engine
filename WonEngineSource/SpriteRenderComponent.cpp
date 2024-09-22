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
	, RemoveRGB{255, 0, 255}
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

void Won::SpriteRenderComponent::Render(HDC NewDC)
{
	if (texture == nullptr)
		assert(false);

	Transform* Tr = GetOwner()->GetComponent<Transform>();
	mVector2<float> vc = Tr->GetPosition();
	mVector2<float> Sc = Tr->GetScale();
	float Ro = Tr->GetRotation();


	if (MainCamera != nullptr)
	{
		vc = MainCamera->CaluatePostion(vc);
	}

	if (CharacterRectangle.right == 0 && CharacterRectangle.left == 0 && CharacterRectangle.bottom == 0 &&
		CharacterRectangle.top == 0)
	{
		CharacterRectangle.left = 0;
		CharacterRectangle.top = 0;
		CharacterRectangle.right = texture->GetWidth();
		CharacterRectangle.bottom = texture->GetHeight();
	}


	if (texture->GetTextureType() == WTexture::TextureType::Bmp)
	{
		TransparentBlt(NewDC
			, static_cast<int>(vc.X + StartPosition.X)
			, static_cast<int>(vc.Y + StartPosition.Y)
			, static_cast<int>(texture->GetWidth() * mSize.X * Sc.X)
			, static_cast<int>(texture->GetHeight() * mSize.Y * Sc.Y)
			, texture->GetHDC()
			, static_cast<int>(CharacterRectangle.left)
			, static_cast<int>(CharacterRectangle.top)
			, static_cast<int>(CharacterRectangle.right)
			, static_cast<int>(CharacterRectangle.bottom)
			, RGB(RemoveRGB.X,RemoveRGB.Y,RemoveRGB.Z));
	}
	else if (texture->GetTextureType() == WTexture::TextureType::png)
	{

		Gdiplus::Graphics graphics(NewDC);

		graphics.TranslateTransform(vc.X, vc.Y);
		graphics.RotateTransform(Ro);
		graphics.TranslateTransform(-vc.X, -vc.Y);

		Gdiplus::Rect srcRect
		(
			static_cast<int>(CharacterRectangle.left)
			, static_cast<int>(CharacterRectangle.top)
			, static_cast<int>(CharacterRectangle.right)
			, static_cast<int>(CharacterRectangle.bottom)
		);

		Gdiplus::Rect desRect = { };
		desRect.X = static_cast<int>(vc.X + StartPosition.X);
		desRect.Y = static_cast<int>(vc.Y + StartPosition.Y);

		if (TextureCuttingSize.X == 0 || TextureCuttingSize.Y == 0)
		{
			desRect.Width = static_cast<int>(texture->GetWidth() * mSize.X * Sc.X);
			desRect.Height = static_cast<int>(texture->GetHeight() * mSize.Y * Sc.Y);
		}
		else
		{
			desRect.Width = static_cast<int>(TextureCuttingSize.X * mSize.X * Sc.X);
			desRect.Height = static_cast<int>(TextureCuttingSize.Y * mSize.Y * Sc.Y);

		}


		if (!(RemoveRGB.X == 0 && RemoveRGB.Y == 0 && RemoveRGB.Z == 0))
		{
			Gdiplus::ImageAttributes imgAttr;

			imgAttr.SetColorKey(
				Gdiplus::Color(static_cast<BYTE>(RemoveRGB.X), static_cast<BYTE>(RemoveRGB.Y), static_cast<BYTE>(RemoveRGB.Z)),
				Gdiplus::Color(static_cast<BYTE>(RemoveRGB.X), static_cast<BYTE>(RemoveRGB.Y), static_cast<BYTE>(RemoveRGB.Z)));

			graphics.DrawImage(
				texture->GetImage()
				, desRect
				, srcRect.X
				, srcRect.Y
				, srcRect.Width
				, srcRect.Height,
				Gdiplus::UnitPixel, &imgAttr);
		}
		else
		{
			graphics.DrawImage(
				texture->GetImage()
				, desRect
				, srcRect.X
				, srcRect.Y
				, srcRect.Width
				, srcRect.Height,
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
