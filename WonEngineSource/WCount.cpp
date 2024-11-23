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

	Vector2 StartPosition = mPosition;
	int mOffset = 0;

	for (int i = 0; i < HUDNumber.size(); ++i)
	{

		TransparentBlt(NewDC
			, static_cast<int>(StartPosition.x + mOffset)
			, static_cast<int>(StartPosition.y)
			, static_cast<int>(mSize.x)
			, static_cast<int>(mSize.y)
			, WHUD::GetTexture()->GetHDC()
			, static_cast<int>(HUDNumber[i]->mSheetStartPosition.x)
			, static_cast<int>(HUDNumber[i]->mSheetStartPosition.y)
			, static_cast<int>(HUDNumber[i]->mSize.x)
			, static_cast<int>(HUDNumber[i]->mSize.y)
			, RGB(255, 0, 255));

		StartPosition.x += mSize.x;
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
