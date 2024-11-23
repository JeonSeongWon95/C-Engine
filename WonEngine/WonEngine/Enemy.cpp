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
		MonsterCollider->SetSize(Vector2(50.0f, 50.0f));

		WTexture* MonsterTexture = WResourceManager::Find<WTexture>(L"Ee");
		WAnimator* MonsterAnimator = AddComponent<WAnimator>();
		MonsterAnimator->CreateAnimation(L"Walk", MonsterTexture, Vector2(0, 15), Vector2(18.5, 18.5), Vector2(0, 0), 2, 0.1f);
		MonsterAnimator->CreateAnimation(L"Dead", MonsterTexture, Vector2(37, 15), Vector2(18.5, 18.5),Vector2(0, 0), 1, 0.1f);
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

