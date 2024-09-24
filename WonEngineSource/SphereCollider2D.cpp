#include "SphereCollider2D.h"
#include "Transform.h"
#include "GameObject.h"

Won::SphereCollider2D::SphereCollider2D()
{
}

Won::SphereCollider2D::~SphereCollider2D()
{
}

void Won::SphereCollider2D::Initialize()
{
}

void Won::SphereCollider2D::Update()
{
}

void Won::SphereCollider2D::LateUpdate()
{
}

void Won::SphereCollider2D::Render(HDC NewDC)
{
	Transform* TR = GetOwner()->GetComponent<Transform>();
	mVector2<float> Pos = TR->GetPosition();

	HBRUSH hbr = (HBRUSH)GetStockObject(NULL_BRUSH);
	HPEN BluePen = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));

	HBRUSH OldBrush = (HBRUSH)SelectObject(NewDC, hbr);
	HPEN OldPen = (HPEN)SelectObject(NewDC, BluePen);

	mVector2<float> Offset = GetOffset();
	mVector2<float> Size = GetSize();

	Ellipse(NewDC
		, static_cast<int>(Pos.X + Offset.X)
		, static_cast<int>(Pos.Y + Offset.Y)
		, static_cast<int>(Pos.X + Offset.X + Size.X)
		, static_cast<int>(Pos.Y + Offset.Y + Size.Y));

	SelectObject(NewDC, OldBrush);
	SelectObject(NewDC, OldPen);

	DeleteObject(BluePen);
}
