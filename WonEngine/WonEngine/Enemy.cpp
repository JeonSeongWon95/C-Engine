#include "Enemy.h"

Won::Enemy::Enemy()
{
}

Won::Enemy::~Enemy()
{
}

void Won::Enemy::Initialize()
{
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
