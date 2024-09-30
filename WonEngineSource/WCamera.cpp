#include "WCamera.h"
#include "WGameObject.h"
#include "WTransform.h"
#include "WonApplication.h"

extern Won::WonApplication Engine;

Won::WCamera::WCamera()
	: WComponent(eComponentType::Camera)
	, mTarget(nullptr)
	, mDistance(sVector2<float>(0,0))
	, mLookPosition(sVector2<float>(0,0))
	, mResolution(sVector2<float>(0, 0))
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

	WTransform* cameraTr = GetOwner()->GetComponent<WTransform>();
	cameraTr->SetPos(sVector2<float>(mResolution.X / 2, mResolution.Y / 2));
}

void Won::WCamera::Update()
{

}

void Won::WCamera::LateUpdate()
{
	if (mTarget)
	{
		WTransform* tr = mTarget->GetComponent<WTransform>();
		if (tr == nullptr)
			return;
		mLookPosition = tr->GetPosition();
	}
	else
	{
		WTransform* cameraTr = GetOwner()->GetComponent<WTransform>();
		mLookPosition = cameraTr->GetPosition();
	}

	mDistance = mLookPosition - (mResolution / 2.0f);

}

void Won::WCamera::Render(HDC NewDC)
{

}
