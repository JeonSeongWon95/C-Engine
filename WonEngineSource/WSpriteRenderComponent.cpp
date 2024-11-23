#include "WSpriteRenderComponent.h"
#include "WGameObject.h"
#include "WTransform.h"
#include "WTexture.h"
#include "WRender.h"

Won::WSpriteRenderComponent::WSpriteRenderComponent()
	: WComponent(eComponentType::SpriteRender)
	, texture(nullptr)
	, mSize(1.0f, 1.0f)
	, StartPosition(0.0, 0.0)
	, CharacterRectangle{0, 0, 0, 0}
	, RemoveRGB{255, 0, 255}
{
}

Won::WSpriteRenderComponent::~WSpriteRenderComponent()
{
	texture = nullptr;
}

void Won::WSpriteRenderComponent::Initialize()
{
}

void Won::WSpriteRenderComponent::Update()
{
}

void Won::WSpriteRenderComponent::LateUpdate()
{
}

void Won::WSpriteRenderComponent::Render(HDC NewDC)
{
	if (texture == nullptr)
		assert(false);

	WTransform* Tr = GetOwner()->GetComponent<WTransform>();
	Vector2 vc = Tr->GetPosition();
	Vector2 Sc = Tr->GetScale();
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
		if (texture->IsAlpha())
		{
			BLENDFUNCTION func = {};
			func.BlendOp = AC_SRC_OVER;
			func.BlendFlags = 0;
			func.AlphaFormat = AC_SRC_ALPHA;
			func.SourceConstantAlpha = 255;


			AlphaBlend(NewDC
				, static_cast<int>(vc.x)
				, static_cast<int>(vc.y)
				, static_cast<int>(texture->GetWidth() * mSize.x * Sc.x)
				, static_cast<int>(texture->GetHeight() * mSize.y * Sc.y)
				, texture->GetHDC()
				, static_cast<int>(CharacterRectangle.left)
				, static_cast<int>(CharacterRectangle.top)
				, static_cast<int>(CharacterRectangle.right)
				, static_cast<int>(CharacterRectangle.bottom)
				, func);
		}
		else
		{
			::TransparentBlt(NewDC
				, static_cast<int>(vc.x)
				, static_cast<int>(vc.y)
				, static_cast<int>(texture->GetWidth() * mSize.x * Sc.x)
				, static_cast<int>(texture->GetHeight() * mSize.y * Sc.y)
				, texture->GetHDC()
				, static_cast<int>(CharacterRectangle.left)
				, static_cast<int>(CharacterRectangle.top)
				, static_cast<int>(CharacterRectangle.right)
				, static_cast<int>(CharacterRectangle.bottom)
				, RGB(RemoveRGB.x, RemoveRGB.y, RemoveRGB.z));
		}
	}
	else if (texture->GetTextureType() == WTexture::TextureType::png)
	{

		Gdiplus::Graphics graphics(NewDC);

		graphics.TranslateTransform(vc.x, vc.y);
		graphics.RotateTransform(Ro);
		graphics.TranslateTransform(-vc.x, -vc.y);

		Gdiplus::Rect srcRect
		(
			static_cast<int>(CharacterRectangle.left)
			, static_cast<int>(CharacterRectangle.top)
			, static_cast<int>(CharacterRectangle.right)
			, static_cast<int>(CharacterRectangle.bottom)
		);

		Gdiplus::Rect desRect = { };
		desRect.X = static_cast<int>(vc.x + StartPosition.x);
		desRect.Y = static_cast<int>(vc.y + StartPosition.y);

		if (TextureCuttingSize.x == 0 || TextureCuttingSize.x == 0)
		{
			desRect.Width = static_cast<int>(texture->GetWidth() * mSize.x * Sc.x);
			desRect.Height = static_cast<int>(texture->GetHeight() * mSize.y * Sc.y);
		}
		else
		{
			desRect.Width = static_cast<int>(TextureCuttingSize.x * mSize.x * Sc.x);
			desRect.Height = static_cast<int>(TextureCuttingSize.y * mSize.y * Sc.y);

		}


		if (!(RemoveRGB.x == 0 && RemoveRGB.y == 0 && RemoveRGB.z == 0))
		{
			Gdiplus::ImageAttributes imgAttr;

			imgAttr.SetColorKey(
				Gdiplus::Color(static_cast<BYTE>(RemoveRGB.x), static_cast<BYTE>(RemoveRGB.y), static_cast<BYTE>(RemoveRGB.z)),
				Gdiplus::Color(static_cast<BYTE>(RemoveRGB.x), static_cast<BYTE>(RemoveRGB.y), static_cast<BYTE>(RemoveRGB.z)));

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

void Won::WSpriteRenderComponent::SetTextureSize(int NewWidth, int NewHeight)
{
	if(texture != nullptr)
	{
		TextureCuttingSize.x = NewWidth;
		TextureCuttingSize.y = NewHeight;
 	}
}
