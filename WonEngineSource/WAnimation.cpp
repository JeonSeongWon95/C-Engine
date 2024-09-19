#include "WAnimation.h"
#include "../WonEngineSource/Timer.h"
#include "../WonEngineSource/WAnimator.h"
#include "../WonEngineSource/GameObject.h"
#include "../WonEngineSource/Transform.h"
#include "../WonEngineSource/WRender.h"
#include "../WonEngineSource/WTexture.h"

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

void Won::WAnimation::CreateAnimation(const std::wstring& Name, WTexture* NewText, mVector2<float> StartPosition,
	mVector2<float> SpriteSize, mVector2<float> offset, UINT AnimationSize, float Duration, bool bIsReversal)
{
	MainTexture = NewText;
	SetName(Name);

	if (bIsReversal == false)
	{
		for (int i = 0; i < (int)AnimationSize; ++i)
		{
			Sprite* SP = new Sprite();
			SP->sStartPostion.X = StartPosition.X + (SpriteSize.X * i);
			SP->sStartPostion.Y = StartPosition.Y;
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
			SP->sStartPostion.X = StartPosition.X - (SpriteSize.X * i);
			SP->sStartPostion.Y = StartPosition.Y;
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

	mTimer += Timer::GetDeltaSeconds();

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

	GameObject* GO = Animator->GetOwner();
	Transform* Tr = GO->GetComponent<Transform>();
	mVector2<float> Pos = Tr->GetComponentPosition();
	mVector2<float> Sca = Tr->GetScale();
	float Rot = Tr->GetRotation();
	Sprite* CurrentSprite = Sprites[mIndex];
	HDC ImageDC = MainTexture->GetHDC();
	WTexture::TextureType Type = MainTexture->GetTextureType();

	if (MainCamera != nullptr)
	{
		Pos = MainCamera->CaluatePostion(Pos);
	}

	if (Type == WTexture::TextureType::Bmp)
	{

		BLENDFUNCTION func = {};
		func.BlendOp = AC_SRC_OVER;
		func.BlendFlags = 0;
		func.AlphaFormat = AC_SRC_ALPHA;
		func.SourceConstantAlpha = 255;

		AlphaBlend(NewDC
			, static_cast<int>((Pos.X) - (CurrentSprite->sSize.X / 2.f))
			, static_cast<int>((Pos.Y) - (CurrentSprite->sSize.Y / 2.f))
			, static_cast<int>(CurrentSprite->sSize.X * Sca.X)
			, static_cast<int>(CurrentSprite->sSize.Y * Sca.Y)
			, ImageDC
			, static_cast<int>(CurrentSprite->sStartPostion.X)
			, static_cast<int>(CurrentSprite->sStartPostion.Y)
			, static_cast<int>(CurrentSprite->sSize.X)
			, static_cast<int>(CurrentSprite->sSize.Y), func);
	}
	else if (Type == WTexture::TextureType::png)
	{
		Gdiplus::Graphics graphics(NewDC);
		Gdiplus::ImageAttributes imgAttr;
		
		graphics.TranslateTransform(Pos.X, Pos.Y);
		graphics.RotateTransform(Rot);
		graphics.TranslateTransform(-Pos.X, -Pos.Y);
		

		if(ColorKey.X == -1 && ColorKey.Y == -1 && ColorKey.Z == -1)
		{
			imgAttr.SetColorKey(Gdiplus::Color(255, 0, 255), Gdiplus::Color(255, 0, 255));
		}
		else
		{
			imgAttr.SetColorKey(Gdiplus::Color(ColorKey.X, ColorKey.Y, ColorKey.Z), 
				Gdiplus::Color(ColorKey.X, ColorKey.Y, ColorKey.Z));
		}
		
		graphics.DrawImage(MainTexture->GetImage()
			, Gdiplus::Rect
			( 
				  static_cast<INT>((Pos.X) - (CurrentSprite->sSize.X / 2.f))
				, static_cast<INT>((Pos.Y) - (CurrentSprite->sSize.Y / 2.f))
				, static_cast<INT>((CurrentSprite->sSize.X) * Sca.X)
				, static_cast<INT>((CurrentSprite->sSize.Y) * Sca.Y)
			)
			, static_cast<INT>(CurrentSprite->sStartPostion.X)
			, static_cast<INT>(CurrentSprite->sStartPostion.Y)
			, static_cast<INT>(CurrentSprite->sSize.X)
			, static_cast<INT>(CurrentSprite->sSize.Y)
			, Gdiplus::UnitPixel
			, &imgAttr);

	}

}
