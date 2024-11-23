#include "WButton.h"
#include "WInput.h"

Won::WButton::WButton()
	:mIsOverlap(false)
	,mOnClicked{}
{
}

Won::WButton::~WButton()
{
}

void Won::WButton::OnActive()
{
}

void Won::WButton::OnIsActive()
{
}

void Won::WButton::OnInit()
{
}

void Won::WButton::OnUpdate()
{
	Vector2 MousePos = WInput::GetMousePosition();

	if(mPosition.x < MousePos.x && mPosition.x + mSize.x > MousePos.x 
		&& mPosition.y < MousePos.y && mPosition.y + mSize.y > MousePos.y)
	{
		mIsOverlap = true;
	}
	else
	{
		mIsOverlap = false;
	}

	if(mIsOverlap)
	{
		if(WInput::GetKeyDown(KeyType::LBUTTON))
		{
			OnClicked();
		}
	}
}

void Won::WButton::OnLateUpdate()
{
}

void Won::WButton::OnRender(HDC NewDC)
{
	if(mIsOverlap)
	{
		HBRUSH GreenBrush = CreateSolidBrush(RGB(0, 255, 0));
		HBRUSH OldBrush = (HBRUSH)SelectObject(NewDC, GreenBrush);
		::Rectangle(NewDC, mPosition.x, mPosition.y, mPosition.x + mSize.x, mPosition.y + mSize.y);

		SelectObject(NewDC, OldBrush);
		DeleteObject(GreenBrush);
	}
	else
	{
		::Rectangle(NewDC, mPosition.x, mPosition.y, mPosition.x + mSize.x, mPosition.y + mSize.y);
	}

}

void Won::WButton::Onclear()
{

}

void Won::WButton::OnClicked()
{
	int a = 0;
}



