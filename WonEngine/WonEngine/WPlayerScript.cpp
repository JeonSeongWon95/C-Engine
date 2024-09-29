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
#include "WRigidbody.h"


Won::WPlayerScript::WPlayerScript()
	:mState(ePlayerState::IdleState)
	, Anim(nullptr)
	, Direction(eDirection::RIGHT)
	, Size(ePlayerSize::Small)
	, mPlayerHealth(1)
	, mPlayerIsHit(false)
	, mHitTimer(0.0f)
	, mIsBigger(false)
	, mDeadTimer(0)
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
	default:
		break;
	}

	if (mPlayerIsHit)
	{
		mHitTimer += WTime::GetDeltaSeconds();

		if (mHitTimer > 2)
		{
			mPlayerIsHit = false;
		}
	}

	if(mPlayerHealth <= 0)
	{
		mDeadTimer += WTime::GetDeltaSeconds();

		if(mDeadTimer >= 5)
		{
			WSceneManager::LoadScene(L"EndLevel");
		}
	}

}

void Won::WPlayerScript::LateUpdate()
{
}

void Won::WPlayerScript::Render(HDC NewDC)
{
}

void Won::WPlayerScript::OnColliderEnter(WCollider* Other)
{
}

void Won::WPlayerScript::OnColliderStay(WCollider* Other)
{
}

void Won::WPlayerScript::OnColliderExit(WCollider* Other)
{
}

void Won::WPlayerScript::Idle()
{
	if (mPlayerHealth > 0)
	{
		WRigidbody* RG = GetOwner()->GetComponent<WRigidbody>();
		WTransform* Tr = GetOwner()->GetComponent<WTransform>();

		if (WInput::GetKey(KeyType::UP))
		{

			if (RG->IsGround())
			{
				sVector2<float> Vel = RG->GetVelocity();
				Vel += sVector2<float>(0, -650.0f);
				RG->SetVelocity(Vel);
				RG->SetIsGround(false);

				if ( Size == ePlayerSize::Small)
				{
					if(Direction == eDirection::LEFT)
					{
						Anim->PlayAnimation(L"LeftJumpSmall", false);
					}
					else
					{
						Anim->PlayAnimation(L"RightJumpSmall", false);
					}
				}
				else
				{
					if (Direction == eDirection::LEFT)
					{
						Anim->PlayAnimation(L"LeftJumpBigger", false);
					}
					else
					{
						Anim->PlayAnimation(L"RightJumpBigger", false);
					}
				}

			}
		}

		if (Size == ePlayerSize::Small)
		{
			if (WInput::GetKey(KeyType::LEFT))
			{
				mState = ePlayerState::WalkState;
				Direction = eDirection::LEFT;
				Anim->PlayAnimation(L"LeftWalk", true);
			}
			if (WInput::GetKey(KeyType::RIGHT))
			{
				mState = ePlayerState::WalkState;
				Direction = eDirection::RIGHT;
				Anim->PlayAnimation(L"RightWalk", true);
			}
		}
		else if (Size == ePlayerSize::Bigger)
		{

			if (WInput::GetKey(KeyType::LEFT))
			{
				mState = ePlayerState::WalkState;
				Direction = eDirection::LEFT;
				Anim->PlayAnimation(L"BiggerLeftWalk", true);
			}
			if (WInput::GetKey(KeyType::RIGHT))
			{
				mState = ePlayerState::WalkState;
				Direction = eDirection::RIGHT;
				Anim->PlayAnimation(L"BiggerRightWalk", true);
			}

			if (WInput::GetKeyDown(KeyType::Z))
			{
				Anim->PlayAnimation(L"Attack", false);
			}

		}
	}

}

void Won::WPlayerScript::Walk()
{
	if (mPlayerHealth > 0)
	{
		WTransform* tr = GetOwner()->GetComponent<WTransform>();
		sVector2<float> pos = tr->GetPosition();

		WRigidbody* Rg = GetOwner()->GetComponent<WRigidbody>();

		if (WInput::GetKey(KeyType::LEFT))
		{
			Rg->AddForce(sVector2<float>(-200.0f, 0.0f));
		}
		if (WInput::GetKey(KeyType::RIGHT))
		{
			Rg->AddForce(sVector2<float>(200.0f, 0.0f));
		}

		tr->SetPos(pos);

		if (WInput::GetKeyUp(KeyType::LEFT) || WInput::GetKeyUp(KeyType::RIGHT))
		{
			if (Size == ePlayerSize::Small)
			{
				if (Direction == eDirection::LEFT)
				{
					mState = ePlayerState::IdleState;
					Anim->PlayAnimation(L"LeftIdle", false);
				}
				else if (Direction == eDirection::RIGHT)
				{
					mState = ePlayerState::IdleState;
					Anim->PlayAnimation(L"RightIdle", false);
				}
			}
			else
			{
				if (Direction == eDirection::LEFT)
				{
					mState = ePlayerState::IdleState;
					Anim->PlayAnimation(L"BiggerLeftIdle", false);
				}
				else if (Direction == eDirection::RIGHT)
				{
					mState = ePlayerState::IdleState;
					Anim->PlayAnimation(L"BiggerRightIdle", false);
				}
			}
		}
	}
}

void Won::WPlayerScript::Jump()
{
}

void Won::WPlayerScript::Change()
{
	if (Size == ePlayerSize::Bigger)
		return;

	WTransform* Tr = GetOwner()->GetComponent<WTransform>();
	sVector2<float> Pos = Tr->GetPosition();
	Pos.Y -= 48.0f;
	Tr->SetPos(Pos);

	if (Direction == eDirection::LEFT)
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
	}

	mState = ePlayerState::IdleState;
	Size = ePlayerSize::Bigger;
	mPlayerHealth += 1;
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

	if (WInput::GetKeyUp(KeyType::Z))
	{
		if (Direction == eDirection::LEFT)
		{
			mState = ePlayerState::IdleState;
			Anim->PlayAnimation(L"BiggerLeftIdle", false);
		}
		else if (Direction == eDirection::RIGHT)
		{
			mState = ePlayerState::IdleState;
			Anim->PlayAnimation(L"BiggerRightIdle", false);
		}
	}

}

void Won::WPlayerScript::AddDamage()
{
	if (mPlayerIsHit == false)
	{
		if (mPlayerHealth > 0)
		{
			mPlayerHealth -= 1;
			mPlayerIsHit = true;

			WTransform* Tr = GetOwner()->GetComponent<WTransform>();
			sVector2<float> Pos = Tr->GetPosition();

			if (Direction == eDirection::LEFT)
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
			}

			Pos.Y += 48.0f;
			Tr->SetPos(Pos);

			mState = ePlayerState::IdleState;
			Size = ePlayerSize::Small;
		}
	}

	if (mPlayerHealth <= 0)
	{
		Anim->PlayAnimation(L"Dead", false);
	}
}

void Won::WPlayerScript::AddDamageEnd()
{

}


void Won::WPlayerScript::Dead()
{
	WRigidbody* PlayerRB = GetOwner()->GetComponent<WRigidbody>();
	PlayerRB->SetVelocity(sVector2<float>(0,0));
}


