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
	, Direction(ePlayerDirection::RIGHT)
	, Size(ePlayerSize::Small)
	, mPlayerHealth(3)
	, mPlayerIsHit(false)
	, mHitTimer(0.0f)
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

	if(mPlayerIsHit)
	{
		mHitTimer += WTime::GetDeltaSeconds();

		if(mHitTimer > 2)
		{
			mPlayerIsHit = false;
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
				Vel += sVector2<float>(0, -500.0f);
				RG->SetVelocity(Vel);
				RG->SetIsGround(false);
			}
		}

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
				sVector2<float> Pos = Tr->GetPosition();
				Pos.Y -= 48.0f;
				Tr->SetPos(Pos);


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
				}

				sVector2<float> Pos = Tr->GetPosition();
				Pos.Y += 48.0f;
				Tr->SetPos(Pos);

				mState = ePlayerState::ChangeSize;
				Size = ePlayerSize::Small;
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
			//pos.X -= 100.f * WTime::GetDeltaSeconds();
			Rg->AddForce(sVector2<float>(-200.0f, 0.0f));
		}
		if (WInput::GetKey(KeyType::RIGHT))
		{
			//pos.X += 100.f * WTime::GetDeltaSeconds();
			Rg->AddForce(sVector2<float>(200.0f, 0.0f));
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

	if (WInput::GetKeyUp(KeyType::Z))
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

void Won::WPlayerScript::AddDamage()
{
	if (mPlayerIsHit == false)
	{
		if (mPlayerHealth > 0)
		{
			mPlayerHealth -= 1;

			mPlayerIsHit = true;
		}
	}

	if(mPlayerHealth <= 0)
	{
		Anim->PlayAnimation(L"Dead", false);
	}
}

void Won::WPlayerScript::Dead()
{
	WRigidbody* PlayerRB = GetOwner()->GetComponent<WRigidbody>();
	sVector2<float> Velocity = PlayerRB->GetVelocity();
	Velocity.Y += 500.0f;
	PlayerRB->SetVelocity(Velocity);
}


