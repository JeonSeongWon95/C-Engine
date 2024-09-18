#include "WPlayerScript.h"
#include "GameObject.h"
#include "Transform.h"
#include "Timer.h"
#include "Input.h"
#include "WAnimator.h"
#include "Enemy.h"
#include "../WonEngineSource/WonObject.h"
#include "WEnemyScript.h"
#include "WTexture.h"
#include "ResourceManager.h"


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
	case WPlayerScript::IdleState:
		Idle();
		break;
	case WPlayerScript::WalkState:
		Walk();
		break;
	case WPlayerScript::JumpState:

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
	if (Input::GetKey(KeyType::UP))
	{
		mState = ePlayerState::JumpState;
	}

}

void Won::WPlayerScript::Walk()
{
	Transform* tr = GetOwner()->GetComponent<Transform>();
	mVector2<float> pos = tr->GetComponentPosition();

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
}

void Won::WPlayerScript::Jump()
{
}

void Won::WPlayerScript::SpawnEnemy()
{
	Enemy* Monster = InstanceSpawn<Enemy>(eLayerType::Character);
	Monster->AddComponent<WEnemyScript>();
	Transform* MTR = Monster->GetComponent<Transform>();
	MTR->SetScale(mVector2<float>(3.0f, 3.0f));
	MTR->SetPos(mVector2<float>(500.f, 500.f));
	WTexture* MonsterTexture = ResourceManager::Find<WTexture>(L"Ee");
	WAnimator* MAT = Monster->AddComponent<WAnimator>();
	MAT->CreateAnimation(L"Walk", MonsterTexture, mVector2<float>(0, 15), mVector2<float>(18.5, 18), mVector2<float>(0, 0), 2, 0.1f);
	MAT->PlayAnimation(L"Walk", true);
}
