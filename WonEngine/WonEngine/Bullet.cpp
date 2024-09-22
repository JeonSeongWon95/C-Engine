#include "Bullet.h"

Won::Bullet::Bullet()
{
}

Won::Bullet::~Bullet()
{
}

void Won::Bullet::Initialize()
{
	GameObject::Initialize();
}

void Won::Bullet::Update()
{
	GameObject::Update();
}

void Won::Bullet::LateUpdate()
{
	GameObject::LateUpdate();
}

void Won::Bullet::Render(HDC NewDC)
{
	GameObject::Render(NewDC);
}
