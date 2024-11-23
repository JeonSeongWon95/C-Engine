#include "WUIBase.h"

Won::WUIBase::WUIBase()
	: mPosition(Vector2(0,0))
	, mSize(Vector2(1.0f, 1.0f))
	, mIsFullScreen(false)
	, mEnable(true)
    , mType(eUIType::None)
{
}

Won::WUIBase::~WUIBase()
{
}

void Won::WUIBase::Initialize()
{
	OnInit();
}

void Won::WUIBase::Active()
{
	mEnable = true;
	OnActive();
}

void Won::WUIBase::Update()
{
	OnUpdate();
}

void Won::WUIBase::LateUpdate()
{
	OnLateUpdate();
}

void Won::WUIBase::Render(HDC NewDC)
{
	OnRender(NewDC);
}

void Won::WUIBase::UIClear()
{
	Onclear();
}

void Won::WUIBase::IsActive()
{
	mEnable = false;
	OnIsActive();
}

void Won::WUIBase::OnActive()
{
}

void Won::WUIBase::OnIsActive()
{
}

void Won::WUIBase::OnInit()
{
}

void Won::WUIBase::OnUpdate()
{
}

void Won::WUIBase::OnLateUpdate()
{
}

void Won::WUIBase::OnRender(HDC NewDC)
{
}

void Won::WUIBase::Onclear()
{

}
