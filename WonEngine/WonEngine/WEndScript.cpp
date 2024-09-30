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
	sVector2<float> PlayerPos = PlayerTr->GetPosition();
	sVector2<float> FloorPos = FloorTr->GetPosition();

	float PlayerPosMaxY = PlayerPos.Y + Other->GetSize().Y;
	float FloorPosMaxY = FloorPos.Y + FloorCollider->GetSize().Y;
	float PlayerPosMaxX = PlayerPos.X + Other->GetSize().X;
	float FloorPosMaxX = FloorPos.X + FloorCollider->GetSize().X;
	float PlayerPosMinY = PlayerPos.Y;
	float FloorPosMinY = FloorPos.Y;
	float PlayerPosMinX = PlayerPos.X;
	float FloorPosMinX = FloorPos.X;

	float PlayerVelocityX = PlayerRB->GetVelocity().X;
	float PlayerVelocityY = PlayerRB->GetVelocity().Y;

	float overlapX = min(PlayerPosMaxX, FloorPosMaxX) - max(PlayerPosMinX, FloorPosMinX);
	float overlapY = min(PlayerPosMaxY, FloorPosMaxY) - max(PlayerPosMinY, FloorPosMinY);

	if (overlapX < overlapY)
	{

		if (PlayerVelocityX > 0)
		{
			PlayerPos.X = FloorPosMinX - (PlayerPosMaxX - PlayerPosMinX);
		}
		else if (PlayerVelocityX < 0)
		{
			PlayerPos.X = FloorPosMaxX;
		}

		PlayerVelocityX = 0;
	}

	PlayerTr->SetPos(PlayerPos);
	PlayerRB->SetVelocity(sVector2<float>(PlayerVelocityX, PlayerVelocityY));
	IsEnd = true;
	Other->GetOwner()->SetActive(false);
}

void Won::WEndScript::OnColliderStay(WCollider* Other)
{
}

void Won::WEndScript::OnColliderExit(WCollider* Other)
{
}
