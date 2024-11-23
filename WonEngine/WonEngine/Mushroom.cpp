#include "Mushroom.h"
#include "WMushroomScript.h"
#include "WTexture.h"
#include "WBoxCollider2D.h"
#include "WAnimator.h"
#include "WResourceManager.h"
#include "WTransform.h"
#include "WRigidbody.h"

Won::Mushroom::Mushroom()
	:mIsInit(false)
{
}

Won::Mushroom::~Mushroom()
{
}

void Won::Mushroom::Initialize()
{
	WMushroomScript* MushScript = AddComponent<WMushroomScript>();
	WBoxCollider2D* MushCollider = AddComponent<WBoxCollider2D>();
	WRigidbody* MushRigidbody = AddComponent<WRigidbody>();
	WTransform* MushTransform = GetComponent<WTransform>();
	MushCollider->SetSize(Vector2(50.0f, 50.0f));

	WTexture* MushTexture = WResourceManager::Find<WTexture>(L"It");
	WAnimator* MushAnimator = AddComponent<WAnimator>();

	MushAnimator->CreateAnimation(L"Idle", MushTexture, Vector2(0, 159), Vector2(18, 15), Vector2(0, 0), 1, 0.1f);
	MushAnimator->PlayAnimation(L"Idle", false);

	MushTransform->SetScale(Vector2(3.0f, 3.0f));

	mIsInit = true;

	WGameObject::Initialize();
}

void Won::Mushroom::Update()
{
	WGameObject::Update();

	if (mIsInit)
		return;

	Initialize();
}

void Won::Mushroom::LateUpdate()
{
	WGameObject::LateUpdate();
}

void Won::Mushroom::Render(HDC NewDC)
{
	WGameObject::Render(NewDC);
}
