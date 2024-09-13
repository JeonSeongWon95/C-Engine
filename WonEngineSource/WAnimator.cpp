#include "WAnimator.h"
#include "../WonEngineSource/WAnimation.h"

Won::WAnimator::WAnimator()
	: Component(eComponentType::Animator)
	, Animations{}
	, ActiveAnimation(nullptr)
	, mLoop(false)
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
}

void Won::WAnimator::LateUpdate()
{
}

void Won::WAnimator::Render(HDC NewDC)
{
}

Won::WAnimation* Won::WAnimator::CreateAnimation(std::wstring& Name, mVector2<float> StartPosition, mVector2<float> SpriteSize, 
	mVector2<float> offset, mVector2<float>, bool AnimationCompleted)
{
	 WAnimation* FAnim = FindAnimation(Name);

	 if (FAnim != nullptr)
		 return FAnim;



	return nullptr;
}

Won::WAnimation* Won::WAnimator::FindAnimation(std::wstring& Name)
{
	auto Iter = Animations.find(Name);

	if(Iter == Animations.end())
	{
		return nullptr;
	}

	return Iter->second;
}
