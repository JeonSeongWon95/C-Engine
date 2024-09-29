#include "WHUD.h"
#include "WResourceManager.h"
#include "WTexture.h"
#include "WTimer.h"
#include "WCount.h"
#include "WScore.h"
#include "WRound.h"
#include "WUIBase.h"
#include "WRender.h"

std::vector<Won::WHUD::Number*> Won::WHUD::mNumbers = {};
Won::WTexture* Won::WHUD::mNumberTexture = nullptr;
std::vector<Won::WHUD::WUIBase*> Won::WHUD::mChildUI = {};

Won::WHUD::WHUD()
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
	mNumberTexture = WResourceManager::Find<WTexture>(L"Ti");
	int offset = 0;
	for (int i = 0; i < 10; ++i)
	{
		Number* NewNumber = new Number();
		NewNumber->mSize.X = 8;
		NewNumber->mSize.Y = 8;
		NewNumber->mSheetStartPosition.X = 518 + (i * NewNumber->mSize.X) + offset;
		NewNumber->mSheetStartPosition.Y = 256;

		offset += 1.5;
		mNumbers.push_back(NewNumber);
	}

	WScore* Score = new WScore();
	Score->SetSize(sVector2<float>(20, 20));
	Score->SetPosition(sVector2<float>(100, 50));
	mChildUI.push_back(Score);

	WTimer* Time = new WTimer();
	Time->SetSize(sVector2<float>(20, 20));
	Time->SetPosition(sVector2<float>(610, 50));
	mChildUI.push_back(Time);

	WCount* Count = new WCount();
	Count->SetSize(sVector2<float>(20, 20));
	Count->SetPosition(sVector2<float>(310, 50));
	mChildUI.push_back(Count);

	WRound* Round = new WRound();
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
	sVector2<float> Pos = { 0,0 };

	MainCamera->CaluateTilePosition(Pos);

	TransparentBlt(NewDC
		, Pos.X
		, Pos.Y
		, mNumberTexture->GetWidth()
		, mNumberTexture->GetHeight() * 1.5
		, mNumberTexture->GetHDC()
		, 520
		, 10
		, 256
		, 236
		, RGB(255, 0, 255));


	for (auto UI : mChildUI)
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

void Won::WHUD::AddScore(UINT NewScore)
{
	WScore* CastScore = dynamic_cast<WScore*>(mChildUI[0]);
	CastScore->AddScore(NewScore);
}

void Won::WHUD::AddCount(UINT NewScore)
{
	WCount* CastCount = dynamic_cast<WCount*>(mChildUI[2]);
	CastCount->AddCount(NewScore);
}
