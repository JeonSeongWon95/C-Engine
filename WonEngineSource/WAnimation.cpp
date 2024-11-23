#include "WAnimation.h"
#include "../WonEngineSource/WTime.h"
#include "../WonEngineSource/WAnimator.h"
#include "../WonEngineSource/WGameObject.h"
#include "../WonEngineSource/WTransform.h"
#include "../WonEngineSource/WRender.h"
#include "../WonEngineSource/WTexture.h"
#include "WCollider.h"

Won::WAnimation::WAnimation()
	: WResource(eResourceType::Animation)
	, MainTexture(nullptr)
	, Sprites{}
	, mIndex(-1)
	, bIsCompleted(false)
	, Animator(nullptr)
	, mTimer(0.0)
	, ColorKey(-1, -1, -1)
{

}

Won::WAnimation::~WAnimation()
{
	if(MainTexture)
	{
		MainTexture = nullptr;
	}
	if(Animator)
	{
		Animator = nullptr;
	}
	for(auto Sprite : Sprites)
	{
		delete Sprite;
	}

	Sprites.clear();
}

HRESULT Won::WAnimation::Load(const std::wstring& NewPath)
{
	return E_NOTIMPL;
}

void Won::WAnimation::CreateAnimation(const std::wstring& Name, WTexture* NewText, Vector2 StartPosition,
	Vector2 SpriteSize, Vector2 offset, UINT AnimationSize, float Duration, bool bIsReverse)
{
	MainTexture = NewText;
	SetName(Name);

	if (bIsReverse == false)
	{
		for (int i = 0; i < (int)AnimationSize; ++i)
		{
			Sprite* SP = new Sprite();
			SP->sStartPostion.x = StartPosition.x + (SpriteSize.x * i);
			SP->sStartPostion.y = StartPosition.y;
			SP->sSize = SpriteSize;
			SP->Duration = Duration;
			SP->Offset = offset;

			Sprites.push_back(SP);
		}
	}
	else
	{
		for (int i = 1; i < (int)AnimationSize + 1; ++i)
		{
			Sprite* SP = new Sprite();
			SP->sStartPostion.x = StartPosition.x - (SpriteSize.x * i);
			SP->sStartPostion.y = StartPosition.y;
			SP->sSize = SpriteSize;
			SP->Duration = Duration;
			SP->Offset = offset;

			Sprites.push_back(SP);
		}
	}
}

void Won::WAnimation::Update()
{
	if (bIsCompleted)
		return;

	mTimer += WTime::GetDeltaSeconds();

	if (mTimer > Sprites[mIndex]->Duration)
	{
		mTimer = 0.0;

		if (mIndex < Sprites.size() - 1)
		{
			mIndex++;
		}
		else
		{
			bIsCompleted = true;
		}
	}
}

void Won::WAnimation::Reset()
{
	mTimer = 0.0f;
	mIndex = 0;
	bIsCompleted = false;
}

void Won::WAnimation::Render(HDC NewDC)
{
	if (MainTexture == nullptr)
		return;

	WGameObject* GO = Animator->GetOwner();
	WTransform* Tr = GO->GetComponent<WTransform>();
	Vector2 Pos = Tr->GetPosition();
	Vector2 Sca = Tr->GetScale();
	float Rot = Tr->GetRotation();
	Sprite* CurrentSprite = Sprites[mIndex];
	HDC ImageDC = MainTexture->GetHDC();
	WTexture::TextureType Type = MainTexture->GetTextureType();
	WCollider* Col = GO->GetComponent<WCollider>();

	if (MainCamera != nullptr)
	{
		Pos = MainCamera->CaluatePostion(Pos);
	}

	if (Type == WTexture::TextureType::Bmp)
	{
		
		if(MainTexture->IsAlpha())
		{
			BLENDFUNCTION func = {};
			func.BlendOp = AC_SRC_OVER;
			func.BlendFlags = 0;
			func.AlphaFormat = AC_SRC_ALPHA;
			func.SourceConstantAlpha = 255;


			AlphaBlend(NewDC
				, static_cast<int>(Pos.x)
				, static_cast<int>(Pos.y)
				, static_cast<int>(CurrentSprite->sSize.x * Sca.x)
				, static_cast<int>(CurrentSprite->sSize.y * Sca.y)
				, ImageDC
				, static_cast<int>(CurrentSprite->sStartPostion.x)
				, static_cast<int>(CurrentSprite->sStartPostion.y)
				, static_cast<int>(CurrentSprite->sSize.x)
				, static_cast<int>(CurrentSprite->sSize.y), func);
		}
		else
		{

			TransparentBlt(NewDC
				, static_cast<int>(Pos.x)
				, static_cast<int>(Pos.y)
				, static_cast<int>(CurrentSprite->sSize.x * Sca.x)
				, static_cast<int>(CurrentSprite->sSize.y * Sca.y)
				, ImageDC
				, static_cast<int>(CurrentSprite->sStartPostion.x)
				, static_cast<int>(CurrentSprite->sStartPostion.y)
				, static_cast<int>(CurrentSprite->sSize.x)
				, static_cast<int>(CurrentSprite->sSize.y)
				, RGB(255, 0, 255));
		}

	}
	else if (Type == WTexture::TextureType::png)
	{
		Gdiplus::Graphics graphics(NewDC);
		Gdiplus::ImageAttributes imgAttr;
		
		graphics.TranslateTransform(Pos.x, Pos.y);
		graphics.RotateTransform(Rot);
		graphics.TranslateTransform(-Pos.x, -Pos.y);
		

		if(ColorKey.x == -1 && ColorKey.y == -1 && ColorKey.z == -1)
		{
			imgAttr.SetColorKey(Gdiplus::Color(255, 0, 255), Gdiplus::Color(255, 0, 255));
		}
		else
		{
			imgAttr.SetColorKey(Gdiplus::Color(ColorKey.x, ColorKey.y, ColorKey.z), 
				Gdiplus::Color(ColorKey.x, ColorKey.y, ColorKey.z));
		}
		
		graphics.DrawImage(MainTexture->GetImage()
			, Gdiplus::Rect
			( 
				  static_cast<INT>((Pos.x) - (CurrentSprite->sSize.x / 2.f + CurrentSprite->Offset.x))
				, static_cast<INT>((Pos.y) - (CurrentSprite->sSize.y / 2.f + CurrentSprite->Offset.y))
				, static_cast<INT>((CurrentSprite->sSize.x) * Sca.x)
				, static_cast<INT>((CurrentSprite->sSize.y) * Sca.y)
			)
			, static_cast<INT>(CurrentSprite->sStartPostion.x)
			, static_cast<INT>(CurrentSprite->sStartPostion.y)
			, static_cast<INT>(CurrentSprite->sSize.x)
			, static_cast<INT>(CurrentSprite->sSize.y)
			, Gdiplus::UnitPixel
			, &imgAttr);

	}

}
