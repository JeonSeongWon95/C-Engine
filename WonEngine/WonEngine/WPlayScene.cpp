#include "WPlayScene.h"
#include "WTransform.h"
#include "WSpriteRenderComponent.h"
#include "Player.h"
#include "WInput.h"
#include "WSceneManager.h"
#include "WonObject.h"
#include "WTexture.h"
#include "WResourceManager.h"
#include "WPlayerScript.h"
#include "WCamera.h"
#include "WRender.h"
#include "WAnimator.h"
#include "Enemy.h"
#include "WEnemyScript.h"
#include "WBoxCollider2D.h"
#include "WColliderManager.h"
#include "WSphereCollider2D.h"
#include "TileObject.h"
#include "WTileRenderer.h"
#include "WRigidbody.h"
#include "Floor.h"
#include "WFloorScript.h"
#include "WUIManager.h"
#include "WMushroomScript.h"
#include "Mushroom.h"
#include "Block.h"
#include "ItemBlock.h"
#include "Coin.h"

Won::WPlayScene::WPlayScene()
	: mCharacter(nullptr)
	, mMainCamera(nullptr)
{
}

Won::WPlayScene::~WPlayScene()
{
}

void Won::WPlayScene::Initialize()
{

	FILE* Pfile = nullptr;
	_wfopen_s(&Pfile, L"../Stage", L"rb");
	if (Pfile == nullptr)
		return;
	sVector2<int> SheetIndex;
	sVector2<int> TileIndex;

	while (!feof(Pfile))
	{
		fread(&SheetIndex, sizeof(SheetIndex), 1, Pfile);
		fread(&TileIndex, sizeof(TileIndex), 1, Pfile);
		TileObject* Object = InstanceSpawn<TileObject>(eLayerType::Tilemap);
		WTransform* ObjectTransform = Object->GetComponent<WTransform>();
		ObjectTransform->SetScale(sVector2<float>(3.0f, 3.0f));
		WTileRenderer* TileRender = Object->AddComponent<WTileRenderer>();
		TileRender->SetTexture(WResourceManager::Find<WTexture>(L"Te"));
		ObjectTransform->SetPos(sVector2<float>((TileIndex.X * TileRender->GetSize().X), (TileIndex.Y * TileRender->GetSize().Y)));
		TileRender->SetSheetIndex(SheetIndex);
	}
	fclose(Pfile);

	//Player* HUD = InstanceSpawn<Player>(eLayerType::BackGround);
	//WSpriteRenderComponent* BSRC = HUD->AddComponent<WSpriteRenderComponent>();
	//WTransform* HUDTr = HUD->GetComponent<WTransform>();
	//BSRC->SetTexture(WResourceManager::Find<WTexture>(L"Ti"));
	//BSRC->SetSize(sVector2<float>(4.0f, 4.0f));
	//BSRC->SetStartPosition(sVector2<float>(516, 10));

	WGameObject* Camera = InstanceSpawn<WGameObject>(eLayerType::None);
	WCamera* CameraComponent = Camera->AddComponent<WCamera>();
	WTransform* CameraTransform = Camera->GetComponent<WTransform>();
	mMainCamera = CameraComponent;

	Floor* floor = InstanceSpawn<Floor>(eLayerType::Floor);
	WTransform* floorTr = floor->GetComponent<WTransform>();
	floor->AddComponent<WFloorScript>();
	WBoxCollider2D* floorBx = floor->AddComponent<WBoxCollider2D>();
	floorTr->SetPos(sVector2<float>(0, 575.0f));
	floorTr->SetScale(sVector2<float>(1, 500));
	floorBx->SetSize(sVector2<float>(2360.0f, 50.0f));

	Floor* floortwo = InstanceSpawn<Floor>(eLayerType::Floor);
	WTransform* floortwoTr = floortwo->GetComponent<WTransform>();
	floortwo->AddComponent<WFloorScript>();
	WBoxCollider2D* floortwoBx = floortwo->AddComponent<WBoxCollider2D>();
	floortwoTr->SetPos(sVector2<float>(2450.0f, 575.0f));
	floortwoTr->SetScale(sVector2<float>(1, 500));
	floortwoBx->SetSize(sVector2<float>(480.0f, 50.0f));

	Floor* floorth = InstanceSpawn<Floor>(eLayerType::Floor);
	WTransform* floorthTr = floorth->GetComponent<WTransform>();
	floorth->AddComponent<WFloorScript>();
	WBoxCollider2D* floortrBx = floorth->AddComponent<WBoxCollider2D>();
	floorthTr->SetPos(sVector2<float>(3025.0f, 575.0f));
	floorthTr->SetScale(sVector2<float>(1, 500));
	floortrBx->SetSize(sVector2<float>(810.0f, 50.0f));

	Floor* floorf = InstanceSpawn<Floor>(eLayerType::Floor);
	WTransform* floorfTr = floorf->GetComponent<WTransform>();
	floorf->AddComponent<WFloorScript>();
	WBoxCollider2D* floorfBx = floorf->AddComponent<WBoxCollider2D>();
	floorfTr->SetPos(sVector2<float>(3950.0f, 575.0f));
	floorfTr->SetScale(sVector2<float>(1, 500));
	floorfBx->SetSize(sVector2<float>(310.0f, 50.0f));

	Floor* floorfive = InstanceSpawn<Floor>(eLayerType::Floor);
	WTransform* floorfiveTransform = floorfive->GetComponent<WTransform>();
	floorfive->AddComponent<WFloorScript>();
	WBoxCollider2D* floorfiveCollider = floorfive->AddComponent<WBoxCollider2D>();
	floorfiveTransform->SetPos(sVector2<float>(4380.0f, 575.0f));
	floorfiveTransform->SetScale(sVector2<float>(1, 500));
	floorfiveCollider->SetSize(sVector2<float>(2000.0f, 50.0f));

	mCharacter = InstanceSpawn<Player>(eLayerType::Player);
	WPlayerScript* chScr = mCharacter->AddComponent<WPlayerScript>();
	WRigidbody* ChRg = mCharacter->AddComponent<WRigidbody>();
	ChRg->Setmass(1.5f);

	WBoxCollider2D* PlayerCollider = mCharacter->AddComponent<WBoxCollider2D>();
	PlayerCollider->SetSize(sVector2<float>(50.0f, 50.0f));

	WTransform* CTR = mCharacter->GetComponent<WTransform>();
	CTR->SetScale(sVector2<float>(3.0f, 3.0f));
	CTR->SetPos(sVector2<float>(0, 500.f));

	WTexture* CharcterTexture = WResourceManager::Find<WTexture>(L"Ch");
	WAnimator* CAT = mCharacter->AddComponent<WAnimator>();

	CAT->CreateAnimation(L"RightWalk", CharcterTexture, sVector2<float>(0, 7), sVector2<float>(18.5, 16), sVector2<float>(9.25, 16), 4, 0.1f);
	CAT->CreateAnimation(L"LeftWalk", CharcterTexture, sVector2<float>(570, 221), sVector2<float>(18.5, 16), sVector2<float>(9.25, 16), 4, 0.1f, true);
	CAT->CreateAnimation(L"RightIdle", CharcterTexture, sVector2<float>(0, 7), sVector2<float>(18.5, 16), sVector2<float>(9.25, 16), 1, 0.2f);
	CAT->CreateAnimation(L"LeftIdle", CharcterTexture, sVector2<float>(570, 221), sVector2<float>(18.5, 16), sVector2<float>(9.25, 16), 1, 0.2f, true);
	CAT->CreateAnimation(L"ChangeToRightBigger", CharcterTexture, sVector2<float>(18.5, 72), sVector2<float>(18.5, 32), sVector2<float>(9.25, 32), 2, 0.3f);
	CAT->CreateAnimation(L"ChangeToLeftBigger", CharcterTexture, sVector2<float>(550.5, 285), sVector2<float>(18.5, 32), sVector2<float>(9.25, 32), 2, 0.3f, true);
	CAT->CreateAnimation(L"ChangeToRightSmall", CharcterTexture, sVector2<float>(37, 72), sVector2<float>(18.5, 32), sVector2<float>(9.25, 32), 2, 0.3f, true);
	CAT->CreateAnimation(L"ChangeToLeftSmall", CharcterTexture, sVector2<float>(532, 285), sVector2<float>(18.5, 32), sVector2<float>(9.25, 32), 2, 0.3f);
	CAT->CreateAnimation(L"BiggerRightWalk", CharcterTexture, sVector2<float>(0, 32), sVector2<float>(18.5, 32), sVector2<float>(9.25, 32), 4, 0.1f);
	CAT->CreateAnimation(L"BiggerLeftWalk", CharcterTexture, sVector2<float>(570, 246), sVector2<float>(18.5, 32), sVector2<float>(9.25, 32), 4, 0.1f, true);
	CAT->CreateAnimation(L"BiggerRightIdle", CharcterTexture, sVector2<float>(0, 32), sVector2<float>(18.5, 32), sVector2<float>(9.25, 32), 1, 0.2f);
	CAT->CreateAnimation(L"BiggerLeftIdle", CharcterTexture, sVector2<float>(570, 246), sVector2<float>(18.5, 32), sVector2<float>(9.25, 32), 1, 0.2f, true);
	CAT->CreateAnimation(L"Dead", CharcterTexture, sVector2<float>(115, 7), sVector2<float>(18.5, 16), sVector2<float>(9.25, 32), 1, 0.2f);
	CAT->CreateAnimation(L"LeftJumpSmall", CharcterTexture, sVector2<float>(475, 221), sVector2<float>(18.5, 16), sVector2<float>(9.25, 16), 1, 0.1f, true);
	CAT->CreateAnimation(L"RightJumpSmall", CharcterTexture, sVector2<float>(96.5, 7), sVector2<float>(18.5, 16), sVector2<float>(9.25, 16), 1, 0.1f);
	CAT->CreateAnimation(L"LeftJumpBigger", CharcterTexture, sVector2<float>(455, 246), sVector2<float>(20, 32), sVector2<float>(10, 32), 1, 0.1f);
	CAT->CreateAnimation(L"RightJumpBigger", CharcterTexture, sVector2<float>(96.5, 32), sVector2<float>(20, 32), sVector2<float>(10, 32), 1, 0.1f);
	CAT->CreateAnimation(L"Attack", CharcterTexture, sVector2<float>(135, 73), sVector2<float>(20, 32), sVector2<float>(10, 32), 1, 0.1f);
	CAT->GetStartEvent(L"Attack") = std::bind(&WPlayerScript::Fire, chScr);
	CAT->GetStartEvent(L"Dead") = std::bind(&WPlayerScript::Dead, chScr);
	CAT->PlayAnimation(L"RightIdle", false);

	Enemy* Monster = InstanceSpawn<Enemy>(eLayerType::Character);
	WTransform* MonsterTransform = Monster->GetComponent<WTransform>();
	MonsterTransform->SetScale(sVector2<float>(3.0f, 3.0f));
	MonsterTransform->SetPos(sVector2<float>(500.f, 500.f));

	Mushroom* Mush = InstanceSpawn<Mushroom>(eLayerType::Item);
	WTransform* MushTransform = Mush->GetComponent<WTransform>();
	MushTransform->SetPos(sVector2<float>(100.0f, 300.0f));

	ItemBlock* Itemblock = InstanceSpawn<ItemBlock>(eLayerType::Character);
	WTransform* ItemblockTransform = Itemblock->GetComponent<WTransform>();
	ItemblockTransform->SetScale(sVector2<float>(3.0f, 3.0f));
	ItemblockTransform->SetPos(sVector2<float>(300, 300));

	Block* block = InstanceSpawn<Block>(eLayerType::Character);
	WTransform* blockTransform = block->GetComponent<WTransform>();
	blockTransform->SetScale(sVector2<float>(3.0f, 3.0f));
	blockTransform->SetPos(sVector2<float>(200, 400));

	Coin* coin = InstanceSpawn<Coin>(eLayerType::Item);
	WTransform* coinTransform = coin->GetComponent<WTransform>();
	coinTransform->SetScale(sVector2<float>(3.0f, 3.0f));
	coinTransform->SetPos(sVector2<float>(100, 500));

	WScene::Initialize();
}

void Won::WPlayScene::Update()
{
	WScene::Update();
}

void Won::WPlayScene::LateUpdate()
{
	WScene::LateUpdate();
}

void Won::WPlayScene::Render(HDC NewDC)
{
	WScene::Render(NewDC);
}

void Won::WPlayScene::OnEnter()
{
	MainCamera = mMainCamera;
	MainCamera->SetTarget(mCharacter);

	WColliderManager::SetColliderEnable(eLayerType::Player, eLayerType::Item, true);
	WColliderManager::SetColliderEnable(eLayerType::Player, eLayerType::Character, true);
	WColliderManager::SetColliderEnable(eLayerType::Player, eLayerType::Floor, true);

	WUIManager::Push(eUIType::HUD);
	//WUIManager::Push(eUIType::Button);
}

void Won::WPlayScene::OnExit()
{
	WUIManager::Pop(eUIType::HUD);
	WColliderManager::Clear();
	//WUIManager::Pop(eUIType::Button);
}
