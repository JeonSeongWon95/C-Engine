#include "WCount.h"
#include "WHUD.h"
#include "WTexture.h"

Won::WCount::WCount()
	:mCount(0)
{
}

Won::WCount::~WCount()
{
}

void Won::WCount::OnActive()
{
}

void Won::WCount::OnIsActive()
{
}

void Won::WCount::OnInit()
{
}

void Won::WCount::OnUpdate()
{
}

void Won::WCount::OnLateUpdate()
{
}

void Won::WCount::OnRender(HDC NewDC)
{
	UINT tens = (mCount / 10) % 10;
	UINT ones = mCount % 10;

	std::vector<UINT> Numbers = { tens, ones };
	std::vector<WHUD::Number*> HUDNumber = {};

	for (auto Number : Numbers)
	{
		HUDNumber.push_back(WHUD::GetNumber(Number));
	}

	sVector2<float> StartPosition = mPosition;
	int mOffset = 0;

	for (int i = 0; i < HUDNumber.size(); ++i)
	{

		TransparentBlt(NewDC
			, static_cast<int>(StartPosition.X + mOffset)
			, static_cast<int>(StartPosition.Y)
			, static_cast<int>(mSize.X)
			, static_cast<int>(mSize.Y)
			, WHUD::GetTexture()->GetHDC()
			, static_cast<int>(HUDNumber[i]->mSheetStartPosition.X)
			, static_cast<int>(HUDNumber[i]->mSheetStartPosition.Y)
			, static_cast<int>(HUDNumber[i]->mSize.X)
			, static_cast<int>(HUDNumber[i]->mSize.Y)
			, RGB(255, 0, 255));

		StartPosition.X += mSize.X;
		mOffset += 5;
	}

	mOffset = 0;
}

void Won::WCount::Onclear()
{
}

void Won::WCount::AddCount(UINT NewScore)
{
	if(mCount == 99)
	{
		mCount = 0;
	}
	else
	{
		mCount += NewScore;
	}
}
