#include "WCamera.h"
#include "GameObject.h"
#include "Transform.h"
#include "WonApplication.h"

extern Won::WonApplication Engine;

Won::WCamera::WCamera()
	: Component(eComponentType::Camera)
	, mTarget(nullptr)
	, mDistance(mVector2<float>(0,0))
	, mLookPosition(mVector2<float>(0,0))
	, mResolution(mVector2<float>(0, 0))
{

}

Won::WCamera::~WCamera()
{
	mTarget = nullptr;
}

void Won::WCamera::Initialize()
{
	mResolution.X = static_cast<float>(Engine.GetWidth());
	mResolution.Y = static_cast<float>(Engine.GetHeight());

	Transform* cameraTr = GetOwner()->GetComponent<Transform>();
	cameraTr->SetPos(mVector2<float>(mResolution.X / 2, mResolution.Y / 2));
}

void Won::WCamera::Update()
{

}

void Won::WCamera::LateUpdate()
{
	if (mTarget)
	{
		Transform* tr = mTarget->GetComponent<Transform>();
		mLookPosition = tr->GetPosition();
	}
	else
	{
		Transform* cameraTr = GetOwner()->GetComponent<Transform>();
		mLookPosition = cameraTr->GetPosition();
	}

	mDistance = mLookPosition - (mResolution / 2.0f);

}

void Won::WCamera::Render(HDC NewDC)
{

}
