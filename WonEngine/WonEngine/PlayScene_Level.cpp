#include "PlayScene_Level.h"
#include "Transform.h"
#include "SpriteRenderComponent.h"
#include "Player.h"
#include "Input.h"
#include "Scene_LevelManager.h"
#include "WonObject.h"
#include "WTexture.h"
#include "ResourceManager.h"
#include "WPlayerScript.h"
#include "WCamera.h"
#include "WRender.h"
#include "WAnimator.h"
#include "Enemy.h"
#include "WEnemyScript.h"

Won::PlayScene_Level::PlayScene_Level()
{
}

Won::PlayScene_Level::~PlayScene_Level()
{
}
 
void Won::PlayScene_Level::Initialize()
{
	Player* BG = InstanceSpawn<Player>(eLayerType::BackGround);
	SpriteRenderComponent* BSRC = BG->AddComponent<SpriteRenderComponent>();
	BSRC->SetTexture(ResourceManager::Find<WTexture>(L"Ba"));
	BSRC->SetSize(mVector2<float>(4.0f, 4.0f));
	BSRC->SetStartPosition(mVector2<float>(0, -325));

	//Player* Effect = InstanceSpawn<Player>(eLayerType::Effect);
	//WTexture* EffectTexture = ResourceManager::Find<WTexture>(L"Ef");
	//WAnimator* CATS = Effect->AddComponent<WAnimator>();
	//CATS->CreateAnimation(L"Attack", EffectTexture, mVector2<float>(0, 0), mVector2<float>(200, 322), mVector2<float>(0, 0), 10, 0.1f);
	//CATS->PlayAnimation(L"Attack", true);
	//CATS->SetRemoveColor(mVector3<int>(0, 0, 0));

	Player* Ch = InstanceSpawn<Player>(eLayerType::Player);
	WPlayerScript* chScr =  Ch->AddComponent<WPlayerScript>();
	Transform* CTR = Ch->GetComponent<Transform>();
	CTR->SetScale(mVector2<float>(3.0f, 3.0f));
	CTR->SetPos(mVector2<float>(0, 500.f));
	WTexture* CharcterTexture = ResourceManager::Find<WTexture>(L"Ch");
	WAnimator* CAT = Ch->AddComponent<WAnimator>();
	CAT->CreateAnimation(L"RightWalk", CharcterTexture, mVector2<float>(0, 8), mVector2<float>(18.5, 15.5), mVector2<float>(0, 0), 4, 0.1f);
	CAT->CreateAnimation(L"LeftWalk", CharcterTexture, mVector2<float>(568, 222), mVector2<float>(18.5, 15.5), mVector2<float>(0, 0), 4, 0.1f, true);
	CAT->CreateAnimation(L"RightIdle", CharcterTexture, mVector2<float>(0, 8), mVector2<float>(18.5, 15.5), mVector2<float>(0, 0), 1, 0.2f);
	CAT->CreateAnimation(L"LeftIdle", CharcterTexture, mVector2<float>(568, 222), mVector2<float>(18.5, 15.5), mVector2<float>(0, 0), 1, 0.2f, true);
	
	CAT->GetCompleteEvent(L"RightWalk") = std::bind(&WPlayerScript::SpawnEnemy, chScr);

	//CAT->CreateAnimation(L"RightBigger", CharcterTexture, mVector2<float>(568, 222), mVector2<float>(18.5, 15.5), mVector2<float>(0, 0), 1, 0.2f);
	//CAT->CreateAnimation(L"RightSmall", CharcterTexture, mVector2<float>(568, 222), mVector2<float>(18.5, 15.5), mVector2<float>(0, 0), 1, 0.2f);
	//CAT->CreateAnimation(L"LeftSmall", CharcterTexture, mVector2<float>(568, 222), mVector2<float>(18.5, 15.5), mVector2<float>(0, 0), 1, 0.2f);
	//CAT->CreateAnimation(L"LeftBigger", CharcterTexture, mVector2<float>(568, 222), mVector2<float>(18.5, 15.5), mVector2<float>(0, 0), 1, 0.2f);
	//CAT->CreateAnimation(L"BiggerRightWalk", CharcterTexture, mVector2<float>(568, 222), mVector2<float>(18.5, 15.5), mVector2<float>(0, 0), 1, 0.2f);
	//CAT->CreateAnimation(L"BiggerLeftWalk", CharcterTexture, mVector2<float>(568, 222), mVector2<float>(18.5, 15.5), mVector2<float>(0, 0), 1, 0.2f);
	//CAT->CreateAnimation(L"RightJump", CharcterTexture, mVector2<float>(568, 222), mVector2<float>(18.5, 15.5), mVector2<float>(0, 0), 1, 0.2f);
	//CAT->CreateAnimation(L"LeftJump", CharcterTexture, mVector2<float>(568, 222), mVector2<float>(18.5, 15.5), mVector2<float>(0, 0), 1, 0.2f);
	//CAT->CreateAnimation(L"BiggerLeftJump", CharcterTexture, mVector2<float>(568, 222), mVector2<float>(18.5, 15.5), mVector2<float>(0, 0), 1, 0.2f);
	//CAT->CreateAnimation(L"BiggerLeftJump", CharcterTexture, mVector2<float>(568, 222), mVector2<float>(18.5, 15.5), mVector2<float>(0, 0), 1, 0.2f);

	CAT->PlayAnimation(L"RightIdle", false);

	//Enemy* Monster = InstanceSpawn<Enemy>(eLayerType::Character);
	//Monster->AddComponent<WEnemyScript>();
	//Transform* MTR = Monster->GetComponent<Transform>();
	//MTR->SetScale(mVector2<float>(3.0f, 3.0f));
	//MTR->SetPos(mVector2<float>(500.f, 500.f));
	//WTexture* MonsterTexture = ResourceManager::Find<WTexture>(L"Ee");
	//WAnimator* MAT = Monster->AddComponent<WAnimator>();
	//MAT->CreateAnimation(L"Walk", MonsterTexture, mVector2<float>(0, 15), mVector2<float>(18.5, 18), mVector2<float>(0, 0), 2, 0.1f);
	//MAT->PlayAnimation(L"Walk", true);

	Scene_Level::Initialize();
}

void Won::PlayScene_Level::Update()
{
	Scene_Level::Update();
}

void Won::PlayScene_Level::LateUpdate()
{
	Scene_Level::LateUpdate();
}

void Won::PlayScene_Level::Render(HDC NewDC)
{
	Scene_Level::Render(NewDC);
}

void Won::PlayScene_Level::OnEnter()
{

}

void Won::PlayScene_Level::OnExit()
{

}
