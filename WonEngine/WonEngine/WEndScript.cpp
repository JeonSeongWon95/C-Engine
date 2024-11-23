#include "WEndScript.h"
#include "WCollider.h"
#include "WGameObject.h"
#include "WPlayerScript.h"
#include "WonObject.h"
#include "WTransform.h"
#include "WTime.h"
#include "WHUD.h"
#include "WRigidbody.h"
#include "WRender.h"
#include "WSceneManager.h"

Won::WEndScript::WEndScript()
	:EndGametimer(0)
	,IsEnd(false)
{
}

Won::WEndScript::~WEndScript()
{
}

void Won::WEndScript::Initialize()
{

}

void Won::WEndScript::Update()
{
	if(IsEnd)
	{
		EndGametimer += WTime::GetDeltaSeconds();

		if(EndGametimer > 5)
		{
			WSceneManager::LoadScene(L"TitleLevel");
			EndGametimer = 0;
		}
	}
}

void Won::WEndScript::LateUpdate()
{
}

void Won::WEndScript::Render(HDC NewDC)
{
}

void Won::WEndScript::OnColliderEnter(WCollider* Other)
{
	WPlayerScript* PlayerScript = Other->GetOwner()->GetComponent<WPlayerScript>();

	if (PlayerScript == nullptr)
		return;

	WTransform* PlayerTr = Other->GetOwner()->GetComponent<WTransform>();
	WRigidbody* PlayerRB = Other->GetOwner()->GetComponent<WRigidbody>();
	WTransform* FloorTr = GetOwner()->GetComponent<WTransform>();

	WCollider* FloorCollider = GetOwner()->GetComponent<WCollider>();
	Vector2 PlayerPos = PlayerTr->GetPosition();
	Vector2 FloorPos = FloorTr->GetPosition();

	float PlayerPosMaxY = PlayerPos.y + Other->GetSize().y;
	float FloorPosMaxY = FloorPos.y + FloorCollider->GetSize().y;
	float PlayerPosMaxX = PlayerPos.x + Other->GetSize().x;
	float FloorPosMaxX = FloorPos.x + FloorCollider->GetSize().x;
	float PlayerPosMinY = PlayerPos.y;
	float FloorPosMinY = FloorPos.y;
	float PlayerPosMinX = PlayerPos.x;
	float FloorPosMinX = FloorPos.x;

	float PlayerVelocityX = PlayerRB->GetVelocity().x;
	float PlayerVelocityY = PlayerRB->GetVelocity().y;

	float overlapX = min(PlayerPosMaxX, FloorPosMaxX) - max(PlayerPosMinX, FloorPosMinX);
	float overlapY = min(PlayerPosMaxY, FloorPosMaxY) - max(PlayerPosMinY, FloorPosMinY);

	if (overlapX < overlapY)
	{

		if (PlayerVelocityX > 0)
		{
			PlayerPos.x = FloorPosMinX - (PlayerPosMaxX - PlayerPosMinX);
		}
		else if (PlayerVelocityX < 0)
		{
			PlayerPos.x = FloorPosMaxX;
		}

		PlayerVelocityX = 0;
	}

	PlayerTr->SetPos(PlayerPos);
	PlayerRB->SetVelocity(Vector2(PlayerVelocityX, PlayerVelocityY));
	IsEnd = true;
	Other->GetOwner()->SetActive(false);
}

void Won::WEndScript::OnColliderStay(WCollider* Other)
{
}

void Won::WEndScript::OnColliderExit(WCollider* Other)
{
}
