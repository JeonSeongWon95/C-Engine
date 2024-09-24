#include "Transform.h"

Won::Transform::Transform()
	:Component(eComponentType::Transform)
	, Position(0,0)
	, mscale(1, 1)
	, Rotation(0)
{
}

Won::Transform::~Transform()
{
}

void Won::Transform::Initialize()
{
}

void Won::Transform::Update()
{
}

void Won::Transform::LateUpdate()
{
}

void Won::Transform::Render(HDC NewDC)
{
}
