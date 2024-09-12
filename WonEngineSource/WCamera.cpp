#include "WCamera.h"
#include "GameObject.h"
#include "Transform.h"
#include "WonApplication.h"

extern Won::WonApplication Engine;

Won::WCamera::WCamera()
	: Component(ComponentType::Camera)
	, Target(nullptr)
	, mDistance(mVector2<float>(0,0))
	, mLookPosition(mVector2<float>((774/2),(729/2)))
	, mResolution(mVector2<float>(0, 0))
{

}

Won::WCamera::~WCamera()
{

}

void Won::WCamera::Initialize()
{
	mResolution.X = static_cast<float>(Engine.GetWidth());
	mResolution.Y = static_cast<float>(Engine.GetHeight());
}

void Won::WCamera::Update()
{

}

void Won::WCamera::LateUpdate()
{
	if(Target)
	{
		Transform* Tr = Target->GetComponent<Transform>();
		mLookPosition = Tr->GetComponentPosition();
	}

	mDistance = mLookPosition - (mResolution / 2.0f);

}

void Won::WCamera::Render(HDC NewDC)
{

}
