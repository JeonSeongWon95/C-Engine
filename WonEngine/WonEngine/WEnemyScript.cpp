#include "WEnemyScript.h"
#include "WGameObject.h"
#include "WTransform.h"
#include "WTime.h"
#include "WInput.h"
#include "WAnimator.h"
#include "../WonEngineSource/WonObject.h"
#include "WCollider.h"
#include "Player.h"
#include "WPlayerScript.h"

Won::WEnemyScript::WEnemyScript()
	:mState(eEnemyState::IdleState)
	, Anim(nullptr)
	, Direction(eEnemyDirection::RIGHT)
	, mTimer(0.f)
	, mDeathTimer(0.f)
{
	SetName(L"EnemyScript");
}

Won::WEnemyScript::~WEnemyScript()
{
}

void Won::WEnemyScript::Initialize()
{

}

void Won::WEnemyScript::Update()
{
	if (Anim == nullptr)
	{
		Anim = GetOwner()->GetComponent<WAnimator>();
	}

	switch (mState)
	{
	case eEnemyState::IdleState:
		Idle();
		break;
	case eEnemyState::WalkState:
		Walk();
		break;
	default:
		break;
	}
}

void Won::WEnemyScript::LateUpdate()
{
}

void Won::WEnemyScript::Render(HDC NewDC)
{
}

void Won::WEnemyScript::OnColliderEnter(WCollider* Other)
{
	if(Other->GetOwner()->GetLayerType() == eLayerType::Player)
	{
		WTransform* PlayerTr = Other->GetOwner()->GetComponent<WTransform>();
		WTransform* MyTr = this->GetOwner()->GetComponent<WTransform>();
		
		float PlayerFoot = PlayerTr->GetPosition().Y + Other->GetSize().Y;
		float MyHeight = MyTr->GetPosition().Y;

		if (PlayerFoot < MyHeight)
		{
			WAnimator* MyAnim = GetOwner()->GetComponent<WAnimator>();
			MyAnim->PlayAnimation(L"Dead", false);
		}
		else
		{
			WPlayerScript* PlayerScript = Other->GetOwner()->GetComponent<WPlayerScript>();
			PlayerScript->AddDamage();
		}
	}
	
}

void Won::WEnemyScript::OnColliderStay(WCollider* Other)
{
}

void Won::WEnemyScript::OnColliderExit(WCollider* Other)
{
}

void Won::WEnemyScript::Idle()
{
	mTimer += WTime::GetDeltaSeconds();

	if (mTimer > 2.0f)
	{
		int Pattern = rand() % 3;
		mTimer = 0.f;

		switch (Pattern)
		{
		case 0:
			mState = eEnemyState::IdleState;
			break;
		case 1:
			mState = eEnemyState::WalkState;
			Direction = eEnemyDirection::LEFT;
			break;
		case 2:
			mState = eEnemyState::WalkState;
			Direction = eEnemyDirection::RIGHT;
			break;
		default:
			break;
		}
	}

}

void Won::WEnemyScript::Walk()
{
	WTransform* tr = GetOwner()->GetComponent<WTransform>();
	sVector2<float> pos = tr->GetPosition();
	mTimer += WTime::GetDeltaSeconds();

	if (Direction == eEnemyDirection::LEFT)
	{
		pos.X -= 100.f * WTime::GetDeltaSeconds();
	}
	else if (Direction == eEnemyDirection::RIGHT)
	{
		pos.X += 100.f * WTime::GetDeltaSeconds();
	}

	tr->SetPos(pos);

	if(mTimer > 2.0f)
	{
		mTimer = 0.f;
		mState = eEnemyState::IdleState;
	}
}

void Won::WEnemyScript::Dead()
{
	mDeathTimer += WTime::GetDeltaSeconds();

	if (mDeathTimer > 1)
	{
		mDeathTimer = 0;

		Destroy(GetOwner());

	}
}
