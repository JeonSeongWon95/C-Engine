#include "WBoxCollider2D.h"
#include "WGameObject.h"
#include "WTransform.h"
#include "WRender.h"

Won::WBoxCollider2D::WBoxCollider2D()
{
	WCollider::SetColliderType(eColliderType::Box);
}

Won::WBoxCollider2D::~WBoxCollider2D()
{

}

void Won::WBoxCollider2D::Initialize()
{

}

void Won::WBoxCollider2D::Update()
{

}

void Won::WBoxCollider2D::LateUpdate()
{

}

void Won::WBoxCollider2D::Render(HDC NewDC)
{
	WTransform* TR = GetOwner()->GetComponent<WTransform>();
	Vector2 Pos = TR->GetPosition();

	HBRUSH hbr = (HBRUSH)GetStockObject(NULL_BRUSH);
	HPEN BluePen = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));

	HBRUSH OldBrush = (HBRUSH)SelectObject(NewDC, hbr);
	HPEN OldPen = (HPEN)SelectObject(NewDC, BluePen);

	Vector2 Offset = GetOffset();
	Vector2 Size = GetSize();

	if(MainCamera != nullptr)
	{
		Pos = MainCamera->CaluatePostion(Pos);
	}

	::Rectangle(NewDC
		, static_cast<int>(Pos.x)
		, static_cast<int>(Pos.y)
		, static_cast<int>(Pos.x + Size.x)
		, static_cast<int>(Pos.y + Size.y));

	SelectObject(NewDC, OldBrush);
	SelectObject(NewDC, OldPen);

	DeleteObject(BluePen);
}

void Won::WBoxCollider2D::OnColliderEnter(WCollider* Other)
{
	WCollider::OnColliderEnter(Other);
}

void Won::WBoxCollider2D::OnColliderStay(WCollider* Other)
{
	WCollider::OnColliderStay(Other);
}

void Won::WBoxCollider2D::OnColliderExit(WCollider* Other)
{
	WCollider::OnColliderExit(Other);
}
