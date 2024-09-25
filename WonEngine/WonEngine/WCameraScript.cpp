#include "WCameraScript.h"
#include "Transform.h"
#include "Input.h"
#include "GameObject.h"
#include "Timer.h"

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
	Transform* tr = GetOwner()->GetComponent<Transform>();
	mVector2<float> pos = tr->GetPosition();

	if (Input::GetKey(KeyType::LEFT))
	{
		pos.X -= 100.f * Timer::GetDeltaSeconds();
	}
	if (Input::GetKey(KeyType::RIGHT))
	{
		pos.X += 100.f * Timer::GetDeltaSeconds();
	}
	if (Input::GetKey(KeyType::UP))
	{
		pos.Y -= 100.f * Timer::GetDeltaSeconds();
	}
	if (Input::GetKey(KeyType::DOWN))
	{
		pos.Y += 100.f * Timer::GetDeltaSeconds();
	}

	tr->SetPos(pos);
}

void Won::WCameraScript::LateUpdate()
{
}

void Won::WCameraScript::Render(HDC NewDC)
{

}
