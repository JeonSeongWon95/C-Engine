#include "WSphereCollider2D.h"
#include "WTransform.h"
#include "WGameObject.h"

Won::WSphereCollider2D::WSphereCollider2D()
{
	WCollider::SetColliderType(eColliderType::Sphere);
}

Won::WSphereCollider2D::~WSphereCollider2D()
{
}

void Won::WSphereCollider2D::Initialize()
{
}

void Won::WSphereCollider2D::Update()
{
}

void Won::WSphereCollider2D::LateUpdate()
{
}

void Won::WSphereCollider2D::Render(HDC NewDC)
{
	WTransform* TR = GetOwner()->GetComponent<WTransform>();
	sVector2<float> Pos = TR->GetPosition();

	HBRUSH hbr = (HBRUSH)GetStockObject(NULL_BRUSH);
	HPEN BluePen = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));

	HBRUSH OldBrush = (HBRUSH)SelectObject(NewDC, hbr);
	HPEN OldPen = (HPEN)SelectObject(NewDC, BluePen);

	sVector2<float> Offset = GetOffset();
	sVector2<float> Size = GetSize();

	Ellipse(NewDC
		, static_cast<int>(Pos.X + Offset.X)
		, static_cast<int>(Pos.Y + Offset.Y)
		, static_cast<int>(Pos.X + Offset.X + Size.X)
		, static_cast<int>(Pos.Y + Offset.Y + Size.Y));

	SelectObject(NewDC, OldBrush);
	SelectObject(NewDC, OldPen);

	DeleteObject(BluePen);
}

void Won::WSphereCollider2D::OnColliderEnter(WCollider* Other)
{
}

void Won::WSphereCollider2D::OnColliderStay(WCollider* Other)
{
}

void Won::WSphereCollider2D::OnColliderExit(WCollider* Other)
{
}
