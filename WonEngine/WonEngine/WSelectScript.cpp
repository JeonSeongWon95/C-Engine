#include "WSelectScript.h"
#include "WInput.h"
#include "WTransform.h"
#include "WGameObject.h"

Won::WSelectScript::WSelectScript()
	:mPresentSelected(eSelectedOption::PlayerOne)
{
}

Won::WSelectScript::~WSelectScript()
{
}

void Won::WSelectScript::Initialize()
{
	WTransform* Tr = GetOwner()->GetComponent<WTransform>();
	mPresentSelected = eSelectedOption::PlayerOne;
	Tr->SetPos(Vector2(220.0f, 405.0f));
}

void Won::WSelectScript::Update()
{
	if (WInput::GetKey(KeyType::UP))
	{
		if (mPresentSelected == eSelectedOption::PlayerOne)
			return;

		WTransform* Tr = GetOwner()->GetComponent<WTransform>();
		mPresentSelected = eSelectedOption::PlayerOne;
		Tr->SetPos(Vector2(220.0f, 405.0f));
	}

	if (WInput::GetKey(KeyType::DOWN))
	{
		if (mPresentSelected == eSelectedOption::PlayerTwo)
			return;

		WTransform* Tr = GetOwner()->GetComponent<WTransform>();
		mPresentSelected = eSelectedOption::PlayerTwo;
		Tr->SetPos(Vector2(220.0f, 455.0f));
	}
}

void Won::WSelectScript::LateUpdate()
{
}

void Won::WSelectScript::Render(HDC NewDC)
{
}
