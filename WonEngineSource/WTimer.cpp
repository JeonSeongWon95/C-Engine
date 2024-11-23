#include "WTimer.h"
#include "WTime.h"
#include "WHUD.h"
#include "WTexture.h"

Won::WTimer::WTimer()
	:mTime(0.0f)
	,mRenderTime(300)
	,mOffset(0)
{
}

Won::WTimer::~WTimer()
{
}

void Won::WTimer::OnActive()
{
}

void Won::WTimer::OnIsActive()
{
}

void Won::WTimer::OnInit()
{
}

void Won::WTimer::OnUpdate()
{
	mTime += WTime::GetDeltaSeconds();

	if(mTime >= 1)
	{
		mTime = 0;

		if (mRenderTime > 0)
		{
			mRenderTime -= 1;
		}
	}
}

void Won::WTimer::OnLateUpdate()
{
}

void Won::WTimer::OnRender(HDC NewDC)
{
	UINT hundreds = mRenderTime / 100;
	UINT tens = (mRenderTime / 10) % 10;
	UINT ones = mRenderTime % 10;

	WHUD::Number* hundredsNum = nullptr;
	WHUD::Number* tensNum = nullptr;
	WHUD::Number* onesNum = nullptr;
	WHUD::Number* CurrentNum = nullptr;

	hundredsNum = WHUD::GetNumber(hundreds);
	tensNum = WHUD::GetNumber(tens);
	onesNum = WHUD::GetNumber(ones);

	Vector2 StartPosition = mPosition;

	while(onesNum != nullptr)
	{
		CurrentNum = hundredsNum;

		if(hundredsNum == nullptr)
		{
			CurrentNum = tensNum;
		}
		if(tensNum == nullptr)
		{
			CurrentNum = onesNum;
		}

		TransparentBlt(NewDC
			, static_cast<int>(StartPosition.x + mOffset)
			, static_cast<int>(StartPosition.y)
			, static_cast<int>(mSize.x)
			, static_cast<int>(mSize.y)
			, WHUD::GetTexture()->GetHDC()
			, static_cast<int>(CurrentNum->mSheetStartPosition.x)
			, static_cast<int>(CurrentNum->mSheetStartPosition.y)
			, static_cast<int>(CurrentNum->mSize.x)
			, static_cast<int>(CurrentNum->mSize.y)
			, RGB(255,0,255));

		StartPosition.x += mSize.x;
		mOffset += 5;

		if (CurrentNum == hundredsNum)
		{
			hundredsNum = nullptr;
			continue;
		}
		if (CurrentNum == tensNum)
		{
			tensNum = nullptr;
			continue;
		}
		if (CurrentNum == onesNum)
		{
			onesNum = nullptr;
			continue;
		}
	}

	mOffset = 0;
}

void Won::WTimer::Onclear()
{
}
