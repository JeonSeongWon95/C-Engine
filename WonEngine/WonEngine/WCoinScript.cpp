#include "WCoinScript.h"
#include "WPlayerScript.h"
#include "WGameObject.h"
#include "WCollider.h"
#include "WTransform.h"
#include "WTime.h"
#include "WonObject.h"
#include "WHUD.h"

Won::WCoinScript::WCoinScript()
	: mIsEat(false)
	, mUpLocation(0)
{
}

Won::WCoinScript::~WCoinScript()
{
}

void Won::WCoinScript::Initialize()
{
	mUpLocation = GetOwner()->GetComponent<WTransform>()->GetPosition().Y - 50.0f;
}

void Won::WCoinScript::Update()
{
	if(mIsEat)
	{
		WTransform* Transform = GetOwner()->GetComponent<WTransform>();
		sVector2<float> Pos = Transform->GetPosition();

		if(Pos.Y >= mUpLocation - 30.0f)
		{
			Pos.Y -= (100.0f * WTime::GetDeltaSeconds());
			Transform->SetPos(Pos);
		}
		else
		{
			Destroy(GetOwner());
		}
	}
}

void Won::WCoinScript::LateUpdate()
{
}

void Won::WCoinScript::Render(HDC NewDC)
{
}

void Won::WCoinScript::OnColliderEnter(WCollider* Other)
{
	WPlayerScript* PlayerScript = Other->GetOwner()->GetComponent<WPlayerScript>();

	if (PlayerScript == nullptr)
		return;

	if(!mIsEat)
	{
		WHUD::AddCount(1);
	}

	mIsEat = true;
}

void Won::WCoinScript::OnColliderStay(WCollider* Other)
{
}

void Won::WCoinScript::OnColliderExit(WCollider* Other)
{
}
