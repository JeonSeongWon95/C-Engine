#include "WPlayerScript.h"
#include "GameObject.h"
#include "Transform.h"
#include "Timer.h"
#include "Input.h"
#include "WAnimator.h"
#include "Bullet.h"
#include "../WonEngineSource/WonObject.h"
#include "BulletScript.h"
#include "WTexture.h"
#include "ResourceManager.h"
#include "Player.h"
#include "BoxCollider2D.h"


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
		if (Input::GetKey(KeyType::LEFT))
		{
			mState = ePlayerState::WalkState;
			Direction = ePlayerDirection::LEFT;
			Anim->PlayAnimation(L"LeftWalk", true);
		}
		if (Input::GetKey(KeyType::RIGHT))
		{
			mState = ePlayerState::WalkState;
			Direction = ePlayerDirection::RIGHT;
			Anim->PlayAnimation(L"RightWalk", true);
		}

		if (Input::GetKey(KeyType::A))
		{

			if (Direction == ePlayerDirection::LEFT)
			{
				Anim->PlayAnimation(L"ChangeToLeftBigger", false);
			}
			else
			{
				Anim->PlayAnimation(L"ChangeToRightBigger", false);
			}

			BoxCollider2D* BoxCollider = GetOwner()->GetComponent<BoxCollider2D>();
			BoxCollider->SetSize(mVector2<float>(50, 100));
			BoxCollider->Setoffset(mVector2<float>(-18.0f, -10.0f));
			mState = ePlayerState::ChangeSize;
			Size = ePlayerSize::Bigger;
		}
	}
	else if (Size == ePlayerSize::Bigger)
	{

		if (Input::GetKey(KeyType::LEFT))
		{
			mState = ePlayerState::WalkState;
			Direction = ePlayerDirection::LEFT;
			Anim->PlayAnimation(L"BiggerLeftWalk", true);
		}
		if (Input::GetKey(KeyType::RIGHT))
		{
			mState = ePlayerState::WalkState;
			Direction = ePlayerDirection::RIGHT;
			Anim->PlayAnimation(L"BiggerRightWalk", true);
		}
		if (Input::GetKey(KeyType::A))
		{

			if (Direction == ePlayerDirection::LEFT)
			{
				Anim->PlayAnimation(L"ChangeToLeftSmall", false);
			}
			else
			{
				Anim->PlayAnimation(L"ChangeToRightSmall", false);
			}
			BoxCollider2D* BoxCollider = GetOwner()->GetComponent<BoxCollider2D>();
			BoxCollider->SetSize(mVector2<float>(50, 50));
			BoxCollider->Setoffset(mVector2<float>(-18.0f, -25.0f));
			mState = ePlayerState::ChangeSize;
			Size = ePlayerSize::Small;
		}
		if (Input::GetKeyDown(KeyType::LBUTTON))
		{
			Anim->PlayAnimation(L"Attack", false);
		}

	}

}

void Won::WPlayerScript::Walk()
{
	Transform* tr = GetOwner()->GetComponent<Transform>();
	mVector2<float> pos = tr->GetPosition();

	if (Input::GetKey(KeyType::LEFT))
	{
		pos.X -= 100.f * Timer::GetDeltaSeconds();
	}
	if (Input::GetKey(KeyType::RIGHT))
	{
		pos.X += 100.f * Timer::GetDeltaSeconds();
	}

	tr->SetPos(pos);

	if (Input::GetKeyUp(KeyType::LEFT) || Input::GetKeyUp(KeyType::RIGHT))
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
	Transform* TR = Monster->GetComponent<Transform>();
	BulletScript* BS = Monster->AddComponent<BulletScript>();
	TR->SetPos(GetOwner()->GetComponent<Transform>()->GetPosition());
	TR->SetScale(mVector2<float>(3.0f, 3.0f));
	BS->SetPlayer(dynamic_cast<Player*>(GetOwner()));
	BS->SetTargetPos(Input::GetMousePosition());

	WTexture* MonsterTexture = ResourceManager::Find<WTexture>(L"Ch");
	WAnimator* MAT = Monster->AddComponent<WAnimator>();
	MAT->CreateAnimation(L"Flying", MonsterTexture, mVector2<float>(170, 75), mVector2<float>(10, 10), mVector2<float>(0, 0), 4, 0.1f);
	MAT->PlayAnimation(L"Flying", true);

	if (Input::GetKeyUp(KeyType::LBUTTON))
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

	//Transform* MTR = Monster->GetComponent<Transform>();
	//MTR->SetScale(mVector2<float>(3.0f, 3.0f));
	//MTR->SetPos(mVector2<float>(500.f, 500.f));
	// 
	//WTexture* MonsterTexture = ResourceManager::Find<WTexture>(L"Ee");
	//WAnimator* MAT = Monster->AddComponent<WAnimator>();
	//MAT->CreateAnimation(L"Walk", MonsterTexture, mVector2<float>(0, 15), mVector2<float>(18.5, 18), mVector2<float>(0, 0), 2, 0.1f);
	//MAT->PlayAnimation(L"Walk", true);
}


