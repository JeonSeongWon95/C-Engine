#include "WAnimator.h"
#include "../WonEngineSource/WAnimation.h"

Won::WAnimator::WAnimator()
	: WComponent(eComponentType::Animator)
	, mAnimations{}
	, mActiveAnimation(nullptr)
	, mLoop(false)
	, mAnimEvents{}
{
}

Won::WAnimator::~WAnimator()
{
	for(std::map<std::wstring, WAnimation*>::iterator iter = mAnimations.begin();
		iter != mAnimations.end();)
	{
		delete iter->second;
		iter = mAnimations.erase(iter);
	}
	mAnimations.clear();

	for(std::map<std::wstring, Events*>::iterator iter = mAnimEvents.begin();
		iter != mAnimEvents.end();)
	{
		delete iter->second;
		iter = mAnimEvents.erase(iter);
	}

	mAnimEvents.clear();

	if(mActiveAnimation != nullptr)
	{
		mActiveAnimation = nullptr;
	}
}

void Won::WAnimator::Initialize()
{
}

void Won::WAnimator::Update()
{
	if (mActiveAnimation)
	{
		mActiveAnimation->Update();

		Events* mainEvent = FindEvents(mActiveAnimation->GetName());
		if (mainEvent)
		{
			mainEvent->mCompleteEvent();
		}

		if (mActiveAnimation->IsCompleted() == true && mLoop == true)
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
	if (mActiveAnimation)
	{
		mActiveAnimation->Render(NewDC);
	}
}

void Won::WAnimator::CreateAnimation(const std::wstring& Name, WTexture* NewText, Vector2 StartPosition,
	Vector2 SpriteSize, Vector2 offset, UINT AnimationSize, float Duration, bool bIsReverse)
{
	WAnimation* findanim = FindAnimation(Name);

	if (findanim != nullptr)
		return;

	findanim = new WAnimation();
	findanim->CreateAnimation(Name, NewText, StartPosition, SpriteSize, offset, AnimationSize, Duration, bIsReverse);
	findanim->SetAnimator(this);

	Events* NewEvents = new Events();

	mAnimEvents.insert(std::make_pair(Name, NewEvents));
	mAnimations.insert(std::make_pair(Name, findanim));

}

Won::WAnimation* Won::WAnimator::FindAnimation(const std::wstring& Name)
{
	auto Iter = mAnimations.find(Name);

	if (Iter == mAnimations.end())
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

	if (mActiveAnimation)
	{
		Events* mainEvent = FindEvents(mActiveAnimation->GetName());

		if (mainEvent)
		{
			mainEvent->mEndEvent();
		}
	}

	PlayAnim->Reset();
	Events* mainEvent = FindEvents(PlayAnim->GetName());

	if (mainEvent)
	{
		mainEvent->mStartEvent();
	}

	mActiveAnimation = PlayAnim;
	mLoop = bLoop;
}

void Won::WAnimator::SetRemoveColor(Vector3 Newcolor)
{
	if (mActiveAnimation)
		mActiveAnimation->SetRemoveColor(Newcolor);
}

bool Won::WAnimator::IsCompletedActiveAnimation()
{
	return mActiveAnimation->IsCompleted();
}

Won::WAnimator::Event& Won::WAnimator::GetStartEvent(const std::wstring& Name)
{
	Events* FindEv = FindEvents(Name);
	return FindEv->mStartEvent;
}

Won::WAnimator::Event& Won::WAnimator::GetCompleteEvent(const std::wstring& Name)
{
	Events* FindEv = FindEvents(Name);
	return FindEv->mCompleteEvent;
}

Won::WAnimator::Event& Won::WAnimator::GetEndEvent(const std::wstring& Name)
{
	Events* FindEv = FindEvents(Name);
	return FindEv->mEndEvent;
}
