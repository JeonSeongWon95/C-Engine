#include "WCamera.h"
#include "WGameObject.h"
#include "WTransform.h"
#include "WonApplication.h"

extern Won::WonApplication Engine;

Won::WCamera::WCamera()
	: WComponent(eComponentType::Camera)
	, mTarget(nullptr)
	, mDistance(Vector2(0,0))
	, mLookPosition(Vector2(0,0))
	, mResolution(Vector2(0, 0))
{

}

Won::WCamera::~WCamera()
{
	mTarget = nullptr;
}

void Won::WCamera::Initialize()
{
	mResolution.x = static_cast<float>(Engine.GetWidth());
	mResolution.y = static_cast<float>(Engine.GetHeight());

	WTransform* cameraTr = GetOwner()->GetComponent<WTransform>();
	cameraTr->SetPos(Vector2(mResolution.x / 2, mResolution.y / 2));
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
