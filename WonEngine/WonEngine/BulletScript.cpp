#include "BulletScript.h"
#include "Transform.h"
#include "Player.h"
#include "WPlayerScript.h"
#include "Input.h"
#include "Timer.h"
#include "WonObject.h"

Won::BulletScript::BulletScript()
	:Target(nullptr)
	,Pos(0,0)
	,Dr(WPlayerScript::ePlayerDirection::RIGHT)
	,mDeathTimer(0.0f)
{
}

Won::BulletScript::~BulletScript()
{
}

void Won::BulletScript::Initialize()
{
	if(Target != nullptr)
	{
		WPlayerScript* PS = Target->GetComponent<WPlayerScript>();
		Dr = PS->GetPlayerDirection();
	}
}

void Won::BulletScript::Update()
{
	mDeathTimer += Timer::GetDeltaSeconds();

	//Transform* TR = GetOwner()->GetComponent<Transform>();
	//mVector2<float> Distance = Pos - TR->GetPosition();
	//Distance.Nomalize();
	//mVector2<float> CurrentPosition = TR->GetComponentPosition();
	//CurrentPosition += Distance * 100.0f * Timer::GetDeltaSeconds();
	//TR->SetPos(CurrentPosition);

	float radian = cosf( 5 * mDeathTimer);
	Transform* TR = GetOwner()->GetComponent<Transform>();
	mVector2<float> GPOS = TR->GetPosition();
	GPOS += mVector2<float>(1.0f,radian) * 100.0f * Timer::GetDeltaSeconds();
	TR->SetPos(GPOS);

	if(mDeathTimer > 5.0f)
	{
		Destroy(GetOwner());
	}
}

void Won::BulletScript::LateUpdate()
{

}

void Won::BulletScript::Render(HDC NewDC)
{

}
