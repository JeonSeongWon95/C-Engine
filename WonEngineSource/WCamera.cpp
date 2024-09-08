#include "WCamera.h"
#include "GameObject.h"
#include "Transform.h"
#include "WonApplication.h"

extern Won::WonApplication Engine;

Won::WCamera::WCamera()
	: Component(ComponentType::Camera)
	, Target(nullptr)
	, mDistance(FVector2(0,0))
	, mLookPosition(FVector2(478.f,381.f))
	, mResolution(FVector2(0, 0))
{

}

Won::WCamera::~WCamera()
{

}

void Won::WCamera::Initialize()
{
	mResolution.X = Engine.GetWidth();
	mResolution.Y = Engine.GetHeight();
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
