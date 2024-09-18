#include "WAnimator.h"
#include "../WonEngineSource/WAnimation.h"

Won::WAnimator::WAnimator()
	: Component(eComponentType::Animator)
	, mAnimations{}
	, mActiveAnimation(nullptr)
	, mLoop(false)
	, mAnimEvents{}
{
}

Won::WAnimator::~WAnimator()
{
}

void Won::WAnimator::Initialize()
{
}

void Won::WAnimator::Update()
{
	if(mActiveAnimation)
	{
		mActiveAnimation->Update();
		
		Events* mainEvent = FindEvents(mActiveAnimation->GetName());
		mainEvent->mCompleteEvent.mEvent();

		if(mActiveAnimation->IsCompleted() == true && mLoop == true)
		{
			mActiveAnimation->Reset();
		}
	}
}

void Won::WAnimator::LateUpdate()
{
}

void Won::WAnimator::Render(HDC NewDC)
{
	if(mActiveAnimation)
	{
		mActiveAnimation->Render(NewDC);
	}
}

void Won::WAnimator::CreateAnimation(const std::wstring& Name, WTexture* NewText, mVector2<float> StartPosition, 
	mVector2<float> SpriteSize, mVector2<float> offset, UINT AnimationSize, float Duration, bool bIsReversal)
{
	WAnimation* findanim = FindAnimation(Name);
	
	if(findanim != nullptr)
		return;

	findanim = new WAnimation();
	findanim->CreateAnimation(Name, NewText, StartPosition, SpriteSize, offset, AnimationSize, Duration, bIsReversal);
	findanim->SetAnimator(this);

	Events* NewEvents = new Events();

	mAnimEvents.insert(std::make_pair(Name, NewEvents));
	mAnimations.insert(std::make_pair(Name, findanim));
	
}

Won::WAnimation* Won::WAnimator::FindAnimation(const std::wstring& Name)
{
	auto Iter = mAnimations.find(Name);

	if(Iter == mAnimations.end())
	{
		return nullptr;
	}

	return Iter->second;
}

Won::WAnimator::Events* Won::WAnimator::FindEvents(const std::wstring& Name)
{
	auto Iter = mAnimEvents.find(Name);

	if (Iter == mAnimEvents.end())
	{
		return nullptr;
	}

	return Iter->second;
}

void Won::WAnimator::PlayAnimation(const std::wstring& Name, bool bLoop)
{
	WAnimation* PlayAnim = FindAnimation(Name);

	if (PlayAnim == nullptr)
		return;

	if(mActiveAnimation)
	{
		Events* mainEvent = FindEvents(mActiveAnimation->GetName());
		mainEvent->mEndEvent.mEvent();
	}

	PlayAnim->Reset();

	Events* mainEvent = FindEvents(PlayAnim->GetName());
	mainEvent->mCompleteEvent.mEvent();

	mActiveAnimation = PlayAnim;
	mLoop = bLoop;
}

void Won::WAnimator::SetRemoveColor(mVector3<int> Newcolor)
{
	if(mActiveAnimation)
	{
		mActiveAnimation->SetRemoveColor(Newcolor);
	}
}

bool Won::WAnimator::IsCompletedActiveAnimation()
{
	return mActiveAnimation->IsCompleted();
}

std::function<void()> Won::WAnimator::GetStartEvent(const std::wstring& Name)
{
	Events* FindEv = FindEvents(Name);

	if(FindEv != nullptr)
	{
		return FindEv->mStartEvent.mEvent;
	}

	return nullptr;
}

std::function<void()> Won::WAnimator::GetCompleteEvent(const std::wstring& Name)
{
	Events* FindEv = FindEvents(Name);

	if (FindEv != nullptr)
	{
		return FindEv->mCompleteEvent.mEvent;
	}
	return nullptr;
}

std::function<void()> Won::WAnimator::GetEndEvent(const std::wstring& Name)
{
	Events* FindEv = FindEvents(Name);

	if (FindEv != nullptr)
	{
		return FindEv->mEndEvent.mEvent;
	}
	return nullptr;
}
