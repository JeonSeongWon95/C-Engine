#include "WTransform.h"

Won::WTransform::WTransform()
	:WComponent(eComponentType::WTransform)
	, Position(0,0)
	, mscale(1, 1)
	, Rotation(0)
{
}

Won::WTransform::~WTransform()
{
}

void Won::WTransform::Initialize()
{
}

void Won::WTransform::Update()
{
}

void Won::WTransform::LateUpdate()
{
}

void Won::WTransform::Render(HDC NewDC)
{
}
