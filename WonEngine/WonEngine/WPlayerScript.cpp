#include "WPlayerScript.h"
#include "WGameObject.h"
#include "WTransform.h"
#include "WTime.h"
#include "WInput.h"
#include "WAnimator.h"
#include "Bullet.h"
#include "../WonEngineSource/WonObject.h"
#include "WBulletScript.h"
#include "WTexture.h"
#include "WResourceManager.h"
#include "Player.h"
#include "WBoxCollider2D.h"


Won::WPlayerScript::WPlayerScript()
	:mState(ePlayerState::IdleState)
	, Anim(nullptr)
	, Direction(ePlayerDirection::RIGHT)
	, Size(ePlayerSize::Small)
{
	SetName(L"PlayerScript");
}

Won::WPlayerScript::~WPlayerScript()
{
}

void Won::WPlayerScript::Initialize()
{
}

void Won::WPlayerScript::Update()
{
	if (Anim == nullptr)
	{
		Anim = GetOwner()->GetComponent<WAnimator>();
	}

	switch (mState)
	{
	case Won::WPlayerScript::IdleState:
		Idle();
		break;
	case Won::WPlayerScript::WalkState:
		Walk();
		break;;
	case Won::WPlayerScript::JumpState:
		break;
	case Won::WPlayerScript::ChangeSize:
		Change();
		break;
	default:
		break;
	}

}

void Won::WPlayerScript::LateUpdate()
{
}

void Won::WPlayerScript::Render(HDC NewDC)
{
}

void Won::WPlayerScript::Idle()
{
	if (Size == ePlayerSize::Small)
	{
		if (WInput::GetKey(KeyType::LEFT))
		{
			mState = ePlayerState::WalkState;
			Direction = ePlayerDirection::LEFT;
			Anim->PlayAnimation(L"LeftWalk", true);
		}
		if (WInput::GetKey(KeyType::RIGHT))
		{
			mState = ePlayerState::WalkState;
			Direction = ePlayerDirection::RIGHT;
			Anim->PlayAnimation(L"RightWalk", true);
		}

		if (WInput::GetKey(KeyType::A))
		{

			if (Direction == ePlayerDirection::LEFT)
			{
				Anim->PlayAnimation(L"ChangeToLeftBigger", false);
			}
			else
			{
				Anim->PlayAnimation(L"ChangeToRightBigger", false);
			}

			WCollider* mCollider = GetOwner()->GetComponent<WCollider>();
			if (mCollider->GetColliderType() == WCollider::eColliderType::Box)
			{
				mCollider->SetSize(sVector2<float>(50, 100));
				mCollider->Setoffset(sVector2<float>(-18.0f, -10.0f));
			}
			mState = ePlayerState::ChangeSize;
			Size = ePlayerSize::Bigger;
		}
	}
	else if (Size == ePlayerSize::Bigger)
	{

		if (WInput::GetKey(KeyType::LEFT))
		{
			mState = ePlayerState::WalkState;
			Direction = ePlayerDirection::LEFT;
			Anim->PlayAnimation(L"BiggerLeftWalk", true);
		}
		if (WInput::GetKey(KeyType::RIGHT))
		{
			mState = ePlayerState::WalkState;
			Direction = ePlayerDirection::RIGHT;
			Anim->PlayAnimation(L"BiggerRightWalk", true);
		}
		if (WInput::GetKey(KeyType::A))
		{

			if (Direction == ePlayerDirection::LEFT)
			{
				Anim->PlayAnimation(L"ChangeToLeftSmall", false);
			}
			else
			{
				Anim->PlayAnimation(L"ChangeToRightSmall", false);
			}


			WCollider* mCollider = GetOwner()->GetComponent<WCollider>();
			if (mCollider->GetColliderType() == WCollider::eColliderType::Box)
			{
				mCollider->SetSize(sVector2<float>(50, 50));
				mCollider->Setoffset(sVector2<float>(-18.0f, -25.0f));
			}

			mState = ePlayerState::ChangeSize;
			Size = ePlayerSize::Small;
		}
		if (WInput::GetKeyDown(KeyType::LBUTTON))
		{
			Anim->PlayAnimation(L"Attack", false);
		}

	}

}

void Won::WPlayerScript::Walk()
{
	WTransform* tr = GetOwner()->GetComponent<WTransform>();
	sVector2<float> pos = tr->GetPosition();

	if (WInput::GetKey(KeyType::LEFT))
	{
		pos.X -= 100.f * WTime::GetDeltaSeconds();
	}
	if (WInput::GetKey(KeyType::RIGHT))
	{
		pos.X += 100.f * WTime::GetDeltaSeconds();
	}

	tr->SetPos(pos);

	if (WInput::GetKeyUp(KeyType::LEFT) || WInput::GetKeyUp(KeyType::RIGHT))
	{
		if (Size == ePlayerSize::Small)
		{
			if (Direction == ePlayerDirection::LEFT)
			{
				mState = ePlayerState::IdleState;
				Anim->PlayAnimation(L"LeftIdle", false);
			}
			else if (Direction == ePlayerDirection::RIGHT)
			{
				mState = ePlayerState::IdleState;
				Anim->PlayAnimation(L"RightIdle", false);
			}
		}
		else
		{
			if (Direction == ePlayerDirection::LEFT)
			{
				mState = ePlayerState::IdleState;
				Anim->PlayAnimation(L"BiggerLeftIdle", false);
			}
			else if (Direction == ePlayerDirection::RIGHT)
			{
				mState = ePlayerState::IdleState;
				Anim->PlayAnimation(L"BiggerRightIdle", false);
			}
		}
	}
}

void Won::WPlayerScript::Jump()
{
}

void Won::WPlayerScript::Change()
{
	mState = ePlayerState::IdleState;
}

void Won::WPlayerScript::Fire()
{
	Bullet* Monster = InstanceSpawn<Bullet>(eLayerType::Character);
	WTransform* TR = Monster->GetComponent<WTransform>();
	WBulletScript* BS = Monster->AddComponent<WBulletScript>();
	TR->SetPos(GetOwner()->GetComponent<WTransform>()->GetPosition());
	TR->SetScale(sVector2<float>(3.0f, 3.0f));
	BS->SetPlayer(dynamic_cast<Player*>(GetOwner()));
	BS->SetTargetPos(WInput::GetMousePosition());

	WTexture* MonsterTexture = WResourceManager::Find<WTexture>(L"Ch");
	WAnimator* MAT = Monster->AddComponent<WAnimator>();
	MAT->CreateAnimation(L"Flying", MonsterTexture, sVector2<float>(170, 75), sVector2<float>(10, 10), sVector2<float>(0, 0), 4, 0.1f);
	MAT->PlayAnimation(L"Flying", true);

	if (WInput::GetKeyUp(KeyType::LBUTTON))
	{
		if (Direction == ePlayerDirection::LEFT)
		{
			mState = ePlayerState::IdleState;
			Anim->PlayAnimation(L"BiggerLeftIdle", false);
		}
		else if (Direction == ePlayerDirection::RIGHT)
		{
			mState = ePlayerState::IdleState;
			Anim->PlayAnimation(L"BiggerRightIdle", false);
		}
	}

	//WTransform* MTR = Monster->GetComponent<WTransform>();
	//MTR->SetScale(mVector2<float>(3.0f, 3.0f));
	//MTR->SetPos(mVector2<float>(500.f, 500.f));
	// 
	//WTexture* MonsterTexture = WResourceManager::Find<WTexture>(L"Ee");
	//WAnimator* MAT = Monster->AddComponent<WAnimator>();
	//MAT->CreateAnimation(L"Walk", MonsterTexture, mVector2<float>(0, 15), mVector2<float>(18.5, 18), mVector2<float>(0, 0), 2, 0.1f);
	//MAT->PlayAnimation(L"Walk", true);
}


