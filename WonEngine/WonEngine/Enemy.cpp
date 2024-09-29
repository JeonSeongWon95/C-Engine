#include "Enemy.h"
#include "WEnemyScript.h"
#include "WBoxCollider2D.h"
#include "WTexture.h"
#include "WAnimator.h"
#include "WResourceManager.h"
#include "WRigidbody.h"

Won::Enemy::Enemy()
	:EnemyType(eEnemyType::Goomba)
{
}

Won::Enemy::~Enemy()
{
}

void Won::Enemy::Initialize()
{
	if (EnemyType == eEnemyType::Goomba)
	{
		WEnemyScript* MonsterScript = AddComponent<WEnemyScript>();
		WBoxCollider2D* MonsterCollider = AddComponent<WBoxCollider2D>();
		WRigidbody* MonsterRigidbody = AddComponent<WRigidbody>();
		MonsterCollider->SetSize(sVector2<float>(50.0f, 50.0f));

		WTexture* MonsterTexture = WResourceManager::Find<WTexture>(L"Ee");
		WAnimator* MonsterAnimator = AddComponent<WAnimator>();
		MonsterAnimator->CreateAnimation(L"Walk", MonsterTexture, sVector2<float>(0, 15), sVector2<float>(18.5, 18.5), sVector2<float>(0, 0), 2, 0.1f);
		MonsterAnimator->CreateAnimation(L"Dead", MonsterTexture, sVector2<float>(37, 15), sVector2<float>(18.5, 18.5), sVector2<float>(0, 0), 1, 0.1f);
		MonsterAnimator->GetCompleteEvent(L"Dead") = std::bind(&WEnemyScript::Dead, MonsterScript);
		MonsterAnimator->PlayAnimation(L"Walk", true);
	}
	else if(EnemyType == eEnemyType::Koopa)
	{

	}

	WGameObject::Initialize();
}

void Won::Enemy::Update()
{
	WGameObject::Update();
}

void Won::Enemy::LateUpdate()
{
	WGameObject::LateUpdate();
}

void Won::Enemy::Render(HDC NewDC)
{
	WGameObject::Render(NewDC);
}

