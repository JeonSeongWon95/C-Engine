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
#include "BoxCollider2D.h"
#include "ColliderManager.h"
#include "SphereCollider2D.h"
#include "TileObject.h"
#include "TileRenderer.h"

Won::PlayScene_Level::PlayScene_Level()
{
}

Won::PlayScene_Level::~PlayScene_Level()
{
}
 
void Won::PlayScene_Level::Initialize()
{

	FILE* Pfile = nullptr;
	_wfopen_s(&Pfile, L"../Test", L"rb");

	if (Pfile == nullptr)
		return;

	mVector2<int> SheetIndex;
	mVector2<int> TileIndex;

	while (!feof(Pfile))
	{

		fread(&SheetIndex, sizeof(SheetIndex), 1, Pfile);
		fread(&TileIndex, sizeof(TileIndex), 1, Pfile);

		TileObject* Object = InstanceSpawn<TileObject>(eLayerType::Tilemap);
		Transform* ObjectTransform = Object->GetComponent<Transform>();
		ObjectTransform->SetScale(mVector2<float>(3.0f, 3.0f));
		TileRenderer* TileRender = Object->AddComponent<TileRenderer>();
		TileRender->SetTexture(ResourceManager::Find<WTexture>(L"Ob"));
		ObjectTransform->SetPos(mVector2<float>((TileIndex.X * TileRender->GetSize().X), (TileIndex.Y * TileRender->GetSize().Y)));
		TileRender->SetSheetIndex(SheetIndex);

	}

	fclose(Pfile);

	//Player* BG = InstanceSpawn<Player>(eLayerType::BackGround);
	//SpriteRenderComponent* BSRC = BG->AddComponent<SpriteRenderComponent>();
	//BSRC->SetTexture(ResourceManager::Find<WTexture>(L"Ti"));
	//BSRC->SetSize(mVector2<float>(4.0f, 4.0f));
	//BSRC->SetStartPosition(mVector2<float>(0, -325));

	//Player* Effect = InstanceSpawn<Player>(eLayerType::Effect);
	//WTexture* EffectTexture = ResourceManager::Find<WTexture>(L"Ef");
	//WAnimator* CATS = Effect->AddComponent<WAnimator>();
	//CATS->CreateAnimation(L"Attack", EffectTexture, mVector2<float>(0, 0), mVector2<float>(200, 322), mVector2<float>(0, 0), 10, 0.1f);
	//CATS->PlayAnimation(L"Attack", true);
	//CATS->SetRemoveColor(mVector3<int>(0, 0, 0));

	ColliderManager::SetColliderEnable(eLayerType::Player, eLayerType::Character, true);

	Player* Ch = InstanceSpawn<Player>(eLayerType::Player);
	WPlayerScript* chScr =  Ch->AddComponent<WPlayerScript>();

	SphereCollider2D* PlayerCollider = Ch->AddComponent<SphereCollider2D>();
	PlayerCollider->Setoffset(mVector2<float>(-18.0f, -25.0f));
	PlayerCollider->SetSize(mVector2<float>(50.0f, 50.0f));

	Transform* CTR = Ch->GetComponent<Transform>();
	CTR->SetScale(mVector2<float>(3.0f, 3.0f));
	CTR->SetPos(mVector2<float>(0, 500.f));

	WTexture* CharcterTexture = ResourceManager::Find<WTexture>(L"Ch");
	WAnimator* CAT = Ch->AddComponent<WAnimator>();

	CAT->CreateAnimation(L"RightWalk", CharcterTexture, mVector2<float>(0, 7), mVector2<float>(18.5, 16), mVector2<float>(9.25, 16), 4, 0.1f);
	CAT->CreateAnimation(L"LeftWalk", CharcterTexture, mVector2<float>(568, 222), mVector2<float>(18.5, 16), mVector2<float>(9.25, 16), 4, 0.1f, true);
	CAT->CreateAnimation(L"RightIdle", CharcterTexture, mVector2<float>(0, 7), mVector2<float>(18.5, 16), mVector2<float>(9.25, 16), 1, 0.2f);
	CAT->CreateAnimation(L"LeftIdle", CharcterTexture, mVector2<float>(568, 222), mVector2<float>(18.5, 16), mVector2<float>(9.25, 16), 1, 0.2f, true);
	CAT->CreateAnimation(L"ChangeToRightBigger", CharcterTexture, mVector2<float>(18.5, 73), mVector2<float>(18.5, 32), mVector2<float>(9.25, 32), 2, 0.1f);
	CAT->CreateAnimation(L"ChangeToLeftBigger", CharcterTexture, mVector2<float>(550.5, 286), mVector2<float>(18.5, 32), mVector2<float>(9.25, 32), 2, 0.1f, true);
	CAT->CreateAnimation(L"ChangeToRightSmall", CharcterTexture, mVector2<float>(37, 73), mVector2<float>(18.5, 32), mVector2<float>(9.25, 32), 2, 0.1f, true);
	CAT->CreateAnimation(L"ChangeToLeftSmall", CharcterTexture, mVector2<float>(532, 286), mVector2<float>(18.5, 32), mVector2<float>(9.25, 32), 2, 0.1f);
	CAT->CreateAnimation(L"BiggerRightWalk", CharcterTexture, mVector2<float>(0, 33), mVector2<float>(18.5, 32), mVector2<float>(9.25, 32), 4, 0.1f);
	CAT->CreateAnimation(L"BiggerLeftWalk", CharcterTexture, mVector2<float>(568, 247), mVector2<float>(18.5, 32), mVector2<float>(9.25, 32), 4, 0.1f, true);
	CAT->CreateAnimation(L"BiggerRightIdle", CharcterTexture, mVector2<float>(0, 33), mVector2<float>(18.5, 32), mVector2<float>(9.25, 32), 1, 0.2f);
	CAT->CreateAnimation(L"BiggerLeftIdle", CharcterTexture, mVector2<float>(568, 247), mVector2<float>(18.5, 32), mVector2<float>(9.25, 32), 1, 0.2f, true);
	CAT->CreateAnimation(L"Attack", CharcterTexture, mVector2<float>(135, 73), mVector2<float>(20, 32), mVector2<float>(10, 32), 1, 0.1f);
	
	CAT->GetStartEvent(L"Attack") = std::bind(&WPlayerScript::Fire, chScr);
	CAT->PlayAnimation(L"RightIdle", false);

	DestoryOnLoadScene(Ch);

	Enemy* Monster = InstanceSpawn<Enemy>(eLayerType::Character);
	Monster->AddComponent<WEnemyScript>();

	SphereCollider2D* MB = Monster->AddComponent<SphereCollider2D>();
	MB->SetSize(mVector2<float>(50.0f, 50.0f));
	MB->Setoffset(mVector2<float>(-15.0f, -15.0f));

	Transform* MTR = Monster->GetComponent<Transform>();
	MTR->SetScale(mVector2<float>(3.0f, 3.0f));
	MTR->SetPos(mVector2<float>(500.f, 500.f));

	WTexture* MonsterTexture = ResourceManager::Find<WTexture>(L"Ee");
	WAnimator* MAT = Monster->AddComponent<WAnimator>();
	MAT->CreateAnimation(L"Walk", MonsterTexture, mVector2<float>(0, 15), mVector2<float>(18.5, 18), mVector2<float>(0, 0), 2, 0.1f);
	MAT->PlayAnimation(L"Walk", true);

	Scene_Level::Initialize();
}

void Won::PlayScene_Level::Update()
{
	Scene_Level::Update();

	if(Input::GetKey(KeyType::A))
	{
		Scene_LevelManager::LoadScene_Level(L"TitleLevel");
	}
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
