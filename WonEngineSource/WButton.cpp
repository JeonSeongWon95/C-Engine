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
	sVector2<float> MousePos = WInput::GetMousePosition();

	if(mPosition.X < MousePos.X && mPosition.X + mSize.X > MousePos.X 
		&& mPosition.Y < MousePos.Y && mPosition.Y + mSize.Y > MousePos.Y)
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
		Rectangle(NewDC, mPosition.X, mPosition.Y, mPosition.X + mSize.X, mPosition.Y + mSize.Y);

		SelectObject(NewDC, OldBrush);
		DeleteObject(GreenBrush);
	}
	else
	{
		Rectangle(NewDC, mPosition.X, mPosition.Y, mPosition.X + mSize.X, mPosition.Y + mSize.Y);
	}

}

void Won::WButton::Onclear()
{

}

void Won::WButton::OnClicked()
{
	int a = 0;
}



