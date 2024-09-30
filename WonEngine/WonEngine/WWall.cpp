#include "WWall.h"
#include "WBoxCollider2D.h"
#include "WWallScript.h"
#include "WTexture.h"

Won::WWall::WWall()
{
}

Won::WWall::~WWall()
{
}

void Won::WWall::Initialize()
{
	WWallScript* WallScript = AddComponent<WWallScript>();
	WGameObject::Initialize();
}

void Won::WWall::Update()
{
	WGameObject::Update();
}

void Won::WWall::LateUpdate()
{
	WGameObject::LateUpdate();
}

void Won::WWall::Render(HDC NewDC)
{
	WGameObject::Render(NewDC);
}
