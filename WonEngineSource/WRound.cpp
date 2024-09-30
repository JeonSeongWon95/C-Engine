#include "WRound.h"
#include "WHUD.h"
#include "WTexture.h"

Won::WRound::WRound()
	:mRound(11)
{
}

Won::WRound::~WRound()
{
}

void Won::WRound::OnActive()
{
}

void Won::WRound::OnIsActive()
{
}

void Won::WRound::OnInit()
{
}

void Won::WRound::OnUpdate()
{
}

void Won::WRound::OnLateUpdate()
{
}

void Won::WRound::OnRender(HDC NewDC)
{

	UINT tens = (mRound / 10) % 10;
	UINT ones = mRound % 10;

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
		mOffset += 25;
	}

	mOffset = 0;
}

void Won::WRound::Onclear()
{
}
