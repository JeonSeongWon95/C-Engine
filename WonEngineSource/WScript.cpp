#include "WScript.h"
#include "WCollider.h"

Won::WScript::WScript()
	:WComponent(eComponentType::Script)
{
}

Won::WScript::~WScript()
{
}

void Won::WScript::Initialize()
{
}

void Won::WScript::Update()
{
}

void Won::WScript::LateUpdate()
{
}

void Won::WScript::Render(HDC NewDC)
{
}

void Won::WScript::OnColliderEnter(WCollider* Other)
{
}

void Won::WScript::OnColliderStay(WCollider* Other)
{
}

void Won::WScript::OnColliderExit(WCollider* Other)
{
}
