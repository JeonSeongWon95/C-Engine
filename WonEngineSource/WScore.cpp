#include "WScore.h"
#include "WHUD.h"
#include "WTexture.h"

Won::WScore::WScore()
	:mScore(0)
{
}

Won::WScore::~WScore()
{
}

void Won::WScore::OnActive()
{
}

void Won::WScore::OnIsActive()
{
}

void Won::WScore::OnInit()
{
}

void Won::WScore::OnUpdate()
{
}

void Won::WScore::OnLateUpdate()
{
}

void Won::WScore::OnRender(HDC NewDC)
{
	UINT tthousand = (mScore / 10000) % 10;
	UINT thousand = (mScore / 1000) % 10;
	UINT hundreds = (mScore / 100) % 10;
	UINT tens = (mScore / 10) % 10;
	UINT ones = mScore % 10;

	std::vector<UINT> Numbers = { tthousand , thousand, hundreds, tens, ones };
	std::vector<WHUD::Number*> HUDNumber = {};
	
	for(auto Number : Numbers)
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

void Won::WScore::Onclear()
{
}
