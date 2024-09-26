#include "WRigidbody.h"
#include "WTime.h"
#include "WGameObject.h"
#include "WTransform.h"

Won::WRigidbody::WRigidbody()
	:WComponent(eComponentType::Rigidbody)
	, mmass(1.0f)
	, mforce(sVector2<float>(1.0f, 1.0f))
	, mAcceleration(sVector2<float>(0.0f,0.0f))
	, mVeolcity(sVector2<float>(0.0f, 0.0f))
	, mfriction(10.0f)
	, mIsGround(false)
	, mLimitedVelocity(sVector2<float>(200.f, 1000.f))
	, mGravity(sVector2<float>(0.0f, 800.0f))
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

	//중력 계산하기
	if(mIsGround)
	{
		//1. 땅 위에 있을때 우선 중력의 방향을 가져온다.
		sVector2<float> gravity = mGravity;
		gravity.Nomalize();

		//2. 두 벡터의 내적값을 구한다.
		//이 때 중력 벡터는 단위 벡터로 방향만을 뜻하기 때문에 결과로 반환된 값은 중력과 속도의 방향이 얼마나 비슷한가이다.
		//이를 다시 중력의 단위벡터에 곱을 하면 중력의 방향으로 특정 크기(중력과 속도의 벡터 유사도)를 갖는 새로운 벡터를 만들고
		//속도에서 빼주게 된다.
		//즉 중력의 방향으로 작용하는 힘의 벡터를 가속도에서 빼므로서 가속도에 영향을 주는 것이다.
		float Dot = gravity.Dot(mVeolcity);
		mVeolcity -= gravity * Dot;

	}
	else
	{
		mVeolcity += mGravity * WTime::GetDeltaSeconds();
	}

	sVector2<float> gravity = mGravity;
	gravity.Nomalize();
	float Dot = gravity.Dot(mVeolcity);
	gravity = gravity * Dot;

	sVector2<float> sidevector = mVeolcity - gravity;

	if(gravity.Lenth() > mLimitedVelocity.Y)
	{
		gravity.Nomalize();
		gravity = gravity * mLimitedVelocity.Y;
	}
	if(sidevector.Lenth() > mLimitedVelocity.X)
	{
		sidevector.Nomalize();
		sidevector = sidevector * mLimitedVelocity.X;
	}

	mVeolcity = gravity + sidevector;


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
