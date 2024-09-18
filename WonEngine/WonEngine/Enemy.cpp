#include "Enemy.h"

Won::Enemy::Enemy()
{
}

Won::Enemy::~Enemy()
{
}

void Won::Enemy::Initialize()
{
	GameObject::Initialize();
}

void Won::Enemy::Update()
{
	GameObject::Update();
}

void Won::Enemy::LateUpdate()
{
	GameObject::LateUpdate();
}

void Won::Enemy::Render(HDC NewDC)
{
	GameObject::Render(NewDC);
}
