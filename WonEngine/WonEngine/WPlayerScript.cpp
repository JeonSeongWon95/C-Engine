#include "WPlayerScript.h"
#include "GameObject.h"
#include "Transform.h"
#include "Timer.h"
#include "Input.h"


Won::WPlayerScript::WPlayerScript()
{
}

Won::WPlayerScript::~WPlayerScript()
{
}

void Won::WPlayerScript::Initialize()
{
}

void Won::WPlayerScript::Update()
{
	if(Input::GetKey(KeyType::LEFT))
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		FVector2 pos = tr->GetComponentPosition();
		pos.X -= 100.f * Timer::GetDeltaSeconds();
		tr->SetPos(pos);
	}
	if (Input::GetKey(KeyType::RIGHT))
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		FVector2 pos = tr->GetComponentPosition();
		pos.X += 100.f * Timer::GetDeltaSeconds();
		tr->SetPos(pos);
	}
	if (Input::GetKey(KeyType::UP))
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		FVector2 pos = tr->GetComponentPosition();
		pos.Y -= 100.f * Timer::GetDeltaSeconds();
		tr->SetPos(pos);

	}
	if (Input::GetKey(KeyType::DOWN))
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		FVector2 pos = tr->GetComponentPosition();
		pos.Y += 100.f * Timer::GetDeltaSeconds();
		tr->SetPos(pos);
	}
}

void Won::WPlayerScript::LateUpdate()
{
}

void Won::WPlayerScript::Render(HDC NewDC)
{
}
