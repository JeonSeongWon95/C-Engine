#include "WRigidbody.h"
#include "WTime.h"
#include "WGameObject.h"
#include "WTransform.h"

Won::WRigidbody::WRigidbody()
	:WComponent(eComponentType::Rigidbody)
	, mmass(1.0f)
	, mforce(Vector2(1.0f, 1.0f))
	, mAcceleration(Vector2(0.0f,0.0f))
	, mVeolcity(Vector2(0.0f, 0.0f))
	, mfriction(10.0f)
	, mIsGround(false)
	, mLimitedVelocity(Vector2(200.f, 1000.f))
	, mGravity(Vector2(0.0f, 800.0f))
{

}

Won::WRigidbody::~WRigidbody()
{
}

void Won::WRigidbody::Initialize()
{
}

void Won::WRigidbody::Update()
{
	mAcceleration = (mforce / mmass);
	mVeolcity += mAcceleration * WTime::GetDeltaSeconds();

	if(mIsGround)
	{
		Vector2 gravity = mGravity;
		gravity.Normalize();

		float Dot = gravity.Dot(mVeolcity);
		mVeolcity -= gravity * Dot;

	}
	else
	{
		mVeolcity += mGravity * WTime::GetDeltaSeconds();
	}

	Vector2 gravity = mGravity;
	gravity.Normalize();
	float Dot = gravity.Dot(mVeolcity);
	gravity = gravity * Dot;

	Vector2 sidevector = mVeolcity - gravity;

	if(gravity.Length() > mLimitedVelocity.y)
	{
		gravity.Normalize();
		gravity = gravity * mLimitedVelocity.y;
	}
	if(sidevector.Length() > mLimitedVelocity.x)
	{
		sidevector.Normalize();
		sidevector = sidevector * mLimitedVelocity.x;
	}

	mVeolcity = gravity + sidevector;


	if(mVeolcity.x > 0 || mVeolcity.y > 0)
	{
		Vector2 friction = -mVeolcity;
		friction.Normalize();
		friction *= mfriction * mmass * WTime::GetDeltaSeconds();
		mVeolcity += friction;

		if(mVeolcity.x <= 0 && mVeolcity.y <= 0)
		{
			mVeolcity = Vector2(0.0f, 0.0f);
		}
	}

	WTransform* Tr = GetOwner()->GetComponent<WTransform>();
	Vector2 NewPos = Tr->GetPosition() + mVeolcity * WTime::GetDeltaSeconds();
	Tr->SetPos(NewPos);
	mforce = Vector2(0, 0);
}

void Won::WRigidbody::LateUpdate()
{
}

void Won::WRigidbody::Render(HDC NewDC)
{
}
