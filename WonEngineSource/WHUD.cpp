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
	SetUIType(eUIType::HUD);
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
		NewNumber->mSize.x = 8;
		NewNumber->mSize.y = 8;
		NewNumber->mSheetStartPosition.x = 518 + (i * NewNumber->mSize.x) + offset;
		NewNumber->mSheetStartPosition.y = 256;

		offset += 1.5;
		mNumbers.push_back(NewNumber);
	}

	WScore* Score = new WScore();
	Score->SetSize(Vector2(20, 20));
	Score->SetPosition(Vector2(100, 50));
	mChildUI.push_back(Score);

	WTimer* Time = new WTimer();
	Time->SetSize(Vector2(20, 20));
	Time->SetPosition(Vector2(610, 50));
	mChildUI.push_back(Time);

	WCount* Count = new WCount();
	Count->SetSize(Vector2(20, 20));
	Count->SetPosition(Vector2(310, 50));
	mChildUI.push_back(Count);

	WRound* Round = new WRound();
	Round->SetSize(Vector2(20, 20));
	Round->SetPosition(Vector2(460, 50));
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
	Vector2 Pos = { 0,0 };

	if (MainCamera != nullptr)
	{
		MainCamera->CaluateTilePosition(Pos);
	}

	TransparentBlt(NewDC
		, Pos.x
		, Pos.y
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

	if (mChildUI.size() > 0)
	{
		for (auto UI : mChildUI)
		{

			UI->Onclear();
			delete UI;
		}
	}

	mChildUI.clear();
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
