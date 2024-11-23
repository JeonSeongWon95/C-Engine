#include "WCameraScript.h"
#include "WTransform.h"
#include "WInput.h"
#include "WGameObject.h"
#include "WTime.h"

Won::WCameraScript::WCameraScript()
{
	SetName(L"CameraScript");
}

Won::WCameraScript::~WCameraScript()
{
}

void Won::WCameraScript::Initialize()
{
}

void Won::WCameraScript::Update()
{
	WTransform* tr = GetOwner()->GetComponent<WTransform>();
	Vector2 pos = tr->GetPosition();

	if (WInput::GetKey(KeyType::LEFT))
	{
		pos.x -= 100.f * WTime::GetDeltaSeconds();
	}
	if (WInput::GetKey(KeyType::RIGHT))
	{
		pos.x += 100.f * WTime::GetDeltaSeconds();
	}
	if (WInput::GetKey(KeyType::UP))
	{
		pos.y -= 100.f * WTime::GetDeltaSeconds();
	}
	if (WInput::GetKey(KeyType::DOWN))
	{
		pos.y += 100.f * WTime::GetDeltaSeconds();
	}

	tr->SetPos(pos);
}

void Won::WCameraScript::LateUpdate()
{
}

void Won::WCameraScript::Render(HDC NewDC)
{

}

void Won::WCameraScript::OnColliderEnter(WCollider* Other)
{
}

void Won::WCameraScript::OnColliderStay(WCollider* Other)
{
}

void Won::WCameraScript::OnColliderExit(WCollider* Other)
{
}
