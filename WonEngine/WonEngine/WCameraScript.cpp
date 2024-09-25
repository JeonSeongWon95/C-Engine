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
	sVector2<float> pos = tr->GetPosition();

	if (WInput::GetKey(KeyType::LEFT))
	{
		pos.X -= 100.f * WTime::GetDeltaSeconds();
	}
	if (WInput::GetKey(KeyType::RIGHT))
	{
		pos.X += 100.f * WTime::GetDeltaSeconds();
	}
	if (WInput::GetKey(KeyType::UP))
	{
		pos.Y -= 100.f * WTime::GetDeltaSeconds();
	}
	if (WInput::GetKey(KeyType::DOWN))
	{
		pos.Y += 100.f * WTime::GetDeltaSeconds();
	}

	tr->SetPos(pos);
}

void Won::WCameraScript::LateUpdate()
{
}

void Won::WCameraScript::Render(HDC NewDC)
{

}