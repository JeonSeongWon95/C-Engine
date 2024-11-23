#include "WMushroomScript.h"
#include "WCollider.h"
#include "WPlayerScript.h"
#include "WGameObject.h"
#include "WonObject.h"
#include "WTime.h"


Won::WMushroomScript::WMushroomScript()
{
}

Won::WMushroomScript::~WMushroomScript()
{
}

void Won::WMushroomScript::Initialize()
{
	int MoveDirection = rand() % 2;

	switch (MoveDirection)
	{
	case 0:
		mDirection = eDirection::LEFT;
		break;
 	case 1:
 		mDirection = eDirection::RIGHT;
		break;
	default:
		break;
	}
}

void Won::WMushroomScript::Update()
{
	WTransform* tr = GetOwner()->GetComponent<WTransform>();
	Vector2 pos = tr->GetPosition();
	

	if (mDirection == eDirection::LEFT)
	{
		pos.x -= 50.f * WTime::GetDeltaSeconds();
	}
	else if (mDirection == eDirection::RIGHT)
	{
		pos.x += 50.f * WTime::GetDeltaSeconds();
	}

	tr->SetPos(pos);
}

void Won::WMushroomScript::LateUpdate()
{
}

void Won::WMushroomScript::Render(HDC NewDC)
{
}

void Won::WMushroomScript::OnColliderEnter(WCollider* Other)
{

}

void Won::WMushroomScript::OnColliderStay(WCollider* Other)
{
	WPlayerScript* PlayerScript = Other->GetOwner()->GetComponent<WPlayerScript>();

	if(PlayerScript != nullptr)
	{
		Destroy(GetOwner());
		PlayerScript->Change();
	}
}

void Won::WMushroomScript::OnColliderExit(WCollider* Other)
{
}
