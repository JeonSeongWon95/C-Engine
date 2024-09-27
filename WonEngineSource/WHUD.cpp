#include "WHUD.h"
#include "WResourceManager.h"
#include "WTexture.h"
#include "WTimer.h"
#include "WCount.h"
#include "WScore.h"
#include "WRound.h"

std::vector<Won::WHUD::Number*> Won::WHUD::mNumbers = {};
Won::WTexture* Won::WHUD::mNumberTexture = nullptr;

Won::WHUD::WHUD()
	:mChildUI{}
{
}

Won::WHUD::~WHUD()
{
}

void Won::WHUD::OnActive()
{
	for (auto UI : mChildUI)
	{
		UI->OnActive();
	}
}

void Won::WHUD::OnIsActive()
{
	for (auto UI : mChildUI)
	{
		UI->OnIsActive();
	}
}

void Won::WHUD::OnInit()
{
	mNumberTexture = WResourceManager::Find<WTexture>(L"Hu");

	for (int i = 0; i < 10; ++i)
	{
		Number* NewNumber = new Number();

		NewNumber->mSize.X = 10;
		NewNumber->mSize.Y = 10;
		NewNumber->mSheetStartPosition.X = 264 +  (i * NewNumber->mSize.X);
		NewNumber->mSheetStartPosition.Y = 10;

		mNumbers.push_back(NewNumber);
	}

	WTimer* Time = new WTimer();
	mChildUI.push_back(Time);

	WCount* Count = new WCount();
	mChildUI.push_back(Count);

	WRound* Round = new WRound();
	mChildUI.push_back(Round);

	WScore* Score = new WScore();
	mChildUI.push_back(Round);

}

void Won::WHUD::OnUpdate()
{
	for (auto UI : mChildUI)
	{
		UI->OnUpdate();
	}
}

void Won::WHUD::OnLateUpdate()
{
	for (auto UI : mChildUI)
	{
		UI->OnLateUpdate();
	}
}

void Won::WHUD::OnRender(HDC NewDC)
{
	for(auto UI : mChildUI)
	{
		UI->OnRender(NewDC);
	}

}

void Won::WHUD::Onclear()
{
	for (Number* Num : mNumbers)
	{
		delete Num;
	}

	for (auto UI : mChildUI)
	{
		UI->Onclear();
		delete UI;
	}

	mNumbers.clear();
}
