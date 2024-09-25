#include "WRigidbody.h"
#include "WTime.h"
#include "WGameObject.h"
#include "WTransform.h"

Won::WRigidbody::WRigidbody()
	:WComponent(eComponentType::Rigidbody)
	, mmass(1.0f)
	, mforce(sVector2<float>(1, 1))
	, mAcceleration(sVector2<float>(0,0))
	, mVeolcity(sVector2<float>(0, 0))
	, mfriction(10.0f)
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

	if(mVeolcity.X > 0 || mVeolcity.Y > 0)
	{
		sVector2<float> friction = -mVeolcity;
		friction = friction.Nomalize() * mfriction * mmass * WTime::GetDeltaSeconds();
		mVeolcity += friction;

		if(mVeolcity <= sVector2<float>(0.0f,0.0f))
		{
			mVeolcity = sVector2<float>(0.0f, 0.0f);
		}
	}

	WTransform* Tr = GetOwner()->GetComponent<WTransform>();
	sVector2<float> NewPos = Tr->GetPosition() + mVeolcity * WTime::GetDeltaSeconds();
	Tr->SetPos(NewPos);
	mforce = sVector2<float>(0, 0);
}

void Won::WRigidbody::LateUpdate()
{
}

void Won::WRigidbody::Render(HDC NewDC)
{
}