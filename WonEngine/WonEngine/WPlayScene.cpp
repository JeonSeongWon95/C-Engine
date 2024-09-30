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
#include "WWall.h"
#include "WFlag.h"
#include "WFlagScript.h"
#include "WFlagBlock.h"
#include "WFlagBlockScript.h"
#include "WEndScript.h"

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

	WGameObject* Camera = InstanceSpawn<WGameObject>(eLayerType::None);
	WCamera* CameraComponent = Camera->AddComponent<WCamera>();
	WTransform* CameraTransform = Camera->GetComponent<WTransform>();
	mMainCamera = CameraComponent;

	Floor* floor = InstanceSpawn<Floor>(eLayerType::Environment);
	WTransform* floorTr = floor->GetComponent<WTransform>();
	floor->AddComponent<WFloorScript>();
	WBoxCollider2D* floorBx = floor->AddComponent<WBoxCollider2D>();
	floorTr->SetPos(sVector2<float>(0, 575.0f));
	floorTr->SetScale(sVector2<float>(1, 500));
	floorBx->SetSize(sVector2<float>(2360.0f, 50.0f));

	Floor* floortwo = InstanceSpawn<Floor>(eLayerType::Environment);
	WTransform* floortwoTr = floortwo->GetComponent<WTransform>();
	floortwo->AddComponent<WFloorScript>();
	WBoxCollider2D* floortwoBx = floortwo->AddComponent<WBoxCollider2D>();
	floortwoTr->SetPos(sVector2<float>(2450.0f, 575.0f));
	floortwoTr->SetScale(sVector2<float>(1, 500));
	floortwoBx->SetSize(sVector2<float>(480.0f, 50.0f));

	Floor* floorth = InstanceSpawn<Floor>(eLayerType::Environment);
	WTransform* floorthTr = floorth->GetComponent<WTransform>();
	floorth->AddComponent<WFloorScript>();
	WBoxCollider2D* floortrBx = floorth->AddComponent<WBoxCollider2D>();
	floorthTr->SetPos(sVector2<float>(3025.0f, 575.0f));
	floorthTr->SetScale(sVector2<float>(1, 500));
	floortrBx->SetSize(sVector2<float>(810.0f, 50.0f));

	Floor* floorf = InstanceSpawn<Floor>(eLayerType::Environment);
	WTransform* floorfTr = floorf->GetComponent<WTransform>();
	floorf->AddComponent<WFloorScript>();
	WBoxCollider2D* floorfBx = floorf->AddComponent<WBoxCollider2D>();
	floorfTr->SetPos(sVector2<float>(3940.0f, 575.0f));
	floorfTr->SetScale(sVector2<float>(1, 500));
	floorfBx->SetSize(sVector2<float>(310.0f, 50.0f));

	Floor* floorfive = InstanceSpawn<Floor>(eLayerType::Environment);
	WTransform* floorfiveTransform = floorfive->GetComponent<WTransform>();
	floorfive->AddComponent<WFloorScript>();
	WBoxCollider2D* floorfiveCollider = floorfive->AddComponent<WBoxCollider2D>();
	floorfiveTransform->SetPos(sVector2<float>(4380.0f, 575.0f));
	floorfiveTransform->SetScale(sVector2<float>(1, 500));
	floorfiveCollider->SetSize(sVector2<float>(2000.0f, 50.0f));

	WWall* WallOne = InstanceSpawn<WWall>(eLayerType::Environment);
	WTransform* WallOneTransform = WallOne->GetComponent<WTransform>();
	WBoxCollider2D* WallOneCollider = WallOne->AddComponent<WBoxCollider2D>();
	WallOneTransform->SetPos(sVector2<float>(1585.0f, 490.0f));
	WallOneCollider->SetSize(sVector2<float>(85.0f, 100.0f));

	WWall* WallTwo = InstanceSpawn<WWall>(eLayerType::Environment);
	WTransform* WallTwoTransform = WallTwo->GetComponent<WTransform>();
	WBoxCollider2D* WallTwoCollider = WallTwo->AddComponent<WBoxCollider2D>();
	WallTwoTransform->SetPos(sVector2<float>(1880.0f, 440.0f));
	WallTwoCollider->SetSize(sVector2<float>(85.0f, 150.0f));

	WWall* WallThree = InstanceSpawn<WWall>(eLayerType::Environment);
	WTransform* WallThreeTransform = WallThree->GetComponent<WTransform>();
	WBoxCollider2D* WallThreeCollider = WallThree->AddComponent<WBoxCollider2D>();
	WallThreeTransform->SetPos(sVector2<float>(2120.0f, 390.0f));
	WallThreeCollider->SetSize(sVector2<float>(85.0f, 200.0f));

	WWall* WallFour = InstanceSpawn<WWall>(eLayerType::Environment);
	WTransform* WallFourTransform = WallFour->GetComponent<WTransform>();
	WBoxCollider2D* WallFourCollider = WallFour->AddComponent<WBoxCollider2D>();
	WallFourTransform->SetPos(sVector2<float>(3165.0f, 530.0f));
	WallFourCollider->SetSize(sVector2<float>(200.0f, 50.0f));

	WWall* WallFive = InstanceSpawn<WWall>(eLayerType::Environment);
	WTransform* WallFiveTransform = WallFive->GetComponent<WTransform>();
	WBoxCollider2D* WallFiveCollider = WallFive->AddComponent<WBoxCollider2D>();
	WallFiveTransform->SetPos(sVector2<float>(3215.0f, 480.0f));
	WallFiveCollider->SetSize(sVector2<float>(150.0f, 50.0f));

	WWall* WallSix = InstanceSpawn<WWall>(eLayerType::Environment);
	WTransform* WallSixTransform = WallSix->GetComponent<WTransform>();
	WBoxCollider2D* WallSixCollider = WallSix->AddComponent<WBoxCollider2D>();
	WallSixTransform->SetPos(sVector2<float>(3265.0f, 430.0f));
	WallSixCollider->SetSize(sVector2<float>(100.0f, 50.0f));

	WWall* WallSeven = InstanceSpawn<WWall>(eLayerType::Environment);
	WTransform* WallSevenransform = WallSeven->GetComponent<WTransform>();
	WBoxCollider2D* WallSevenCollider = WallSeven->AddComponent<WBoxCollider2D>();
	WallSevenransform->SetPos(sVector2<float>(3315.0f, 380.0f));
	WallSevenCollider->SetSize(sVector2<float>(50.0f, 50.0f));

	WWall* WallEight = InstanceSpawn<WWall>(eLayerType::Environment);
	WTransform* WallEightTransform = WallEight->GetComponent<WTransform>();
	WBoxCollider2D* WallEightCollider = WallEight->AddComponent<WBoxCollider2D>();
	WallEightTransform->SetPos(sVector2<float>(3505.0f, 530.0f));
	WallEightCollider->SetSize(sVector2<float>(150.0f, 50.0f));

	WWall* WallNine = InstanceSpawn<WWall>(eLayerType::Environment);
	WTransform* WallNineTransform = WallNine->GetComponent<WTransform>();
	WBoxCollider2D* WallNineCollider = WallNine->AddComponent<WBoxCollider2D>();
	WallNineTransform->SetPos(sVector2<float>(3505.0f, 480.0f));
	WallNineCollider->SetSize(sVector2<float>(100.0f, 50.0f));

	WWall* WallTen = InstanceSpawn<WWall>(eLayerType::Environment);
	WTransform* WallTenTransform = WallTen->GetComponent<WTransform>();
	WBoxCollider2D* WallTenCollider = WallTen->AddComponent<WBoxCollider2D>();
	WallTenTransform->SetPos(sVector2<float>(3505.0f, 430.0f));
	WallTenCollider->SetSize(sVector2<float>(50.0f, 50.0f));

	WWall* WallEleven = InstanceSpawn<WWall>(eLayerType::Environment);
	WTransform* WallElevenTransform = WallEleven->GetComponent<WTransform>();
	WBoxCollider2D* WallElevenCollider = WallEleven->AddComponent<WBoxCollider2D>();
	WallElevenTransform->SetPos(sVector2<float>(3980.0f, 530.0f));
	WallElevenCollider->SetSize(sVector2<float>(300.0f, 50.0f));

	WWall* Walltwelve = InstanceSpawn<WWall>(eLayerType::Environment);
	WTransform* WalltwelveTransform = Walltwelve->GetComponent<WTransform>();
	WBoxCollider2D* WalltwelveCollider = Walltwelve->AddComponent<WBoxCollider2D>();
	WalltwelveTransform->SetPos(sVector2<float>(4650.0f, 540.0f));
	WalltwelveCollider->SetSize(sVector2<float>(400.0f, 50.0f));

	WWall* WallThirteen = InstanceSpawn<WWall>(eLayerType::Environment);
	WTransform* WallThirteenTransform = WallThirteen->GetComponent<WTransform>();
	WBoxCollider2D* WallThirteenCollider = WallThirteen->AddComponent<WBoxCollider2D>();
	WallThirteenTransform->SetPos(sVector2<float>(4700.0f, 490.0f));
	WallThirteenCollider->SetSize(sVector2<float>(350.0f, 50.0f));

	WWall* WallFourteen = InstanceSpawn<WWall>(eLayerType::Environment);
	WTransform* WallFourteenTransform = WallFourteen->GetComponent<WTransform>();
	WBoxCollider2D* WallFourteenCollider = WallFourteen->AddComponent<WBoxCollider2D>();
	WallFourteenTransform->SetPos(sVector2<float>(4750.0f, 440.0f));
	WallFourteenCollider->SetSize(sVector2<float>(300.0f, 50.0f));

	WWall* Wallfifteen = InstanceSpawn<WWall>(eLayerType::Environment);
	WTransform* WallfifteenTransform = Wallfifteen->GetComponent<WTransform>();
	WBoxCollider2D* WallfifteenCollider = Wallfifteen->AddComponent<WBoxCollider2D>();
	WallfifteenTransform->SetPos(sVector2<float>(4800.0f, 390.0f));
	WallfifteenCollider->SetSize(sVector2<float>(250.0f, 50.0f));

	WWall* Wallsixteen = InstanceSpawn<WWall>(eLayerType::Environment);
	WTransform* WallsixteenTransform = Wallsixteen->GetComponent<WTransform>();
	WBoxCollider2D* WallsixteenCollider = Wallsixteen->AddComponent<WBoxCollider2D>();
	WallsixteenTransform->SetPos(sVector2<float>(4850.0f, 340.0f));
	WallsixteenCollider->SetSize(sVector2<float>(200.0f, 50.0f));

	WWall* Wallseventeen = InstanceSpawn<WWall>(eLayerType::Environment);
	WTransform* WallseventeenTransform = Wallseventeen->GetComponent<WTransform>();
	WBoxCollider2D* WallseventeenCollider = Wallseventeen->AddComponent<WBoxCollider2D>();
	WallseventeenTransform->SetPos(sVector2<float>(4900.0f, 290.0f));
	WallseventeenCollider->SetSize(sVector2<float>(150.0f, 50.0f));

	WWall* Walleighteen = InstanceSpawn<WWall>(eLayerType::Environment);
	WTransform* WalleighteenTransform = Walleighteen->GetComponent<WTransform>();
	WBoxCollider2D* WalleighteenCollider = Walleighteen->AddComponent<WBoxCollider2D>();
	WalleighteenTransform->SetPos(sVector2<float>(4950.0f, 240.0f));
	WalleighteenCollider->SetSize(sVector2<float>(100.0f, 50.0f));

	WFlagBlock* flagblock = InstanceSpawn<WFlagBlock>(eLayerType::Environment);
	WTransform* flagblockTransform = flagblock->GetComponent<WTransform>();
	WBoxCollider2D* flagblockCollider = flagblock->AddComponent<WBoxCollider2D>();
	flagblock->AddComponent<WFlagBlockScript>();
	flagblockTransform->SetPos(sVector2<float>(5280.0f, 525.0f));
	flagblockCollider->SetSize(sVector2<float>(50.0f, 50.0f));

	WGameObject* KingdomWall = InstanceSpawn<WGameObject>(eLayerType::Environment);
	WTransform* KingdomWallTransform = KingdomWall->GetComponent<WTransform>();
	WBoxCollider2D* KingdomWallCollider = KingdomWall->AddComponent<WBoxCollider2D>();
	KingdomWall->AddComponent<WEndScript>();
	KingdomWallTransform->SetPos(sVector2<float>(5750.0f, 200.0f));
	KingdomWallCollider->SetSize(sVector2<float>(10.0f, 400.0f));

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
	CAT->CreateAnimation(L"PickupflagBigger", CharcterTexture, sVector2<float>(156.5, 32), sVector2<float>(20, 32), sVector2<float>(10, 32), 1, 0.1f);
	CAT->CreateAnimation(L"PickupflagSmall", CharcterTexture, sVector2<float>(156.5, 7), sVector2<float>(20, 16), sVector2<float>(10, 32), 1, 0.1f);
	CAT->CreateAnimation(L"Attack", CharcterTexture, sVector2<float>(135, 73), sVector2<float>(20, 32), sVector2<float>(10, 32), 1, 0.1f);
	CAT->GetStartEvent(L"Attack") = std::bind(&WPlayerScript::Fire, chScr);
	CAT->GetStartEvent(L"Dead") = std::bind(&WPlayerScript::Dead, chScr);
	CAT->PlayAnimation(L"RightIdle", false);

	Enemy* Monster = InstanceSpawn<Enemy>(eLayerType::Character);
	WTransform* MonsterTransform = Monster->GetComponent<WTransform>();
	MonsterTransform->SetScale(sVector2<float>(3.0f, 3.0f));
	MonsterTransform->SetPos(sVector2<float>(500.f, 500.f));

	Enemy* Monsterfour = InstanceSpawn<Enemy>(eLayerType::Character);
	WTransform* MonsterfourTransform = Monsterfour->GetComponent<WTransform>();
	MonsterfourTransform->SetScale(sVector2<float>(3.0f, 3.0f));
	MonsterfourTransform->SetPos(sVector2<float>(650.f, 500.f));

	Enemy* Monstertwo = InstanceSpawn<Enemy>(eLayerType::Character);
	WTransform* MonstertwoTransform = Monstertwo->GetComponent<WTransform>();
	MonstertwoTransform->SetScale(sVector2<float>(3.0f, 3.0f));
	MonstertwoTransform->SetPos(sVector2<float>(750.f, 500.f));

	Enemy* Monsterthree = InstanceSpawn<Enemy>(eLayerType::Character);
	WTransform* MonsterthreeTransform = Monsterthree->GetComponent<WTransform>();
	MonsterthreeTransform->SetScale(sVector2<float>(3.0f, 3.0f));
	MonsterthreeTransform->SetPos(sVector2<float>(800.f, 500.f));

	ItemBlock* Itemblock = InstanceSpawn<ItemBlock>(eLayerType::Environment);
	WTransform* ItemblockTransform = Itemblock->GetComponent<WTransform>();
	ItemblockTransform->SetScale(sVector2<float>(3.0f, 3.0f));
	ItemblockTransform->SetPos(sVector2<float>(300, 300));

	Block* block = InstanceSpawn<Block>(eLayerType::Environment);
	WTransform* blockTransform = block->GetComponent<WTransform>();
	blockTransform->SetScale(sVector2<float>(3.0f, 3.0f));
	blockTransform->SetPos(sVector2<float>(200, 400));

	Block* blocka = InstanceSpawn<Block>(eLayerType::Environment);
	WTransform* blockaTransform = blocka->GetComponent<WTransform>();
	blockaTransform->SetScale(sVector2<float>(3.0f, 3.0f));
	blockaTransform->SetPos(sVector2<float>(1000, 400));
	Block* blockb = InstanceSpawn<Block>(eLayerType::Environment);
	WTransform* blockbTransform = blockb->GetComponent<WTransform>();
	blockbTransform->SetScale(sVector2<float>(3.0f, 3.0f));
	blockbTransform->SetPos(sVector2<float>(1050, 400));
	Block* blockc = InstanceSpawn<Block>(eLayerType::Environment);
	WTransform* blockcTransform = blockc->GetComponent<WTransform>();
	blockcTransform->SetScale(sVector2<float>(3.0f, 3.0f));
	blockcTransform->SetPos(sVector2<float>(1100, 400));
	Block* blockd = InstanceSpawn<Block>(eLayerType::Environment);
	WTransform* blockdTransform = blockd->GetComponent<WTransform>();
	blockdTransform->SetScale(sVector2<float>(3.0f, 3.0f));
	blockdTransform->SetPos(sVector2<float>(1150, 400));

	Block* blocke = InstanceSpawn<Block>(eLayerType::Environment);
	WTransform* blockeTransform = blocke->GetComponent<WTransform>();
	blockeTransform->SetScale(sVector2<float>(3.0f, 3.0f));
	blockeTransform->SetPos(sVector2<float>(3125, 200));
	Block* blockf = InstanceSpawn<Block>(eLayerType::Environment);
	WTransform* blockfTransform = blockf->GetComponent<WTransform>();
	blockfTransform->SetScale(sVector2<float>(3.0f, 3.0f));
	blockfTransform->SetPos(sVector2<float>(3175, 200));
	Block* blockg = InstanceSpawn<Block>(eLayerType::Environment);
	WTransform* blockgTransform = blockg->GetComponent<WTransform>();
	blockgTransform->SetScale(sVector2<float>(3.0f, 3.0f));
	blockgTransform->SetPos(sVector2<float>(3600, 200));
	Block* blockh = InstanceSpawn<Block>(eLayerType::Environment);
	WTransform* blockhTransform = blockh->GetComponent<WTransform>();
	blockhTransform->SetScale(sVector2<float>(3.0f, 3.0f));
	blockhTransform->SetPos(sVector2<float>(3850, 200));

	Coin* coin = InstanceSpawn<Coin>(eLayerType::Item);
	WTransform* coinTransform = coin->GetComponent<WTransform>();
	coinTransform->SetScale(sVector2<float>(3.0f, 3.0f));
	coinTransform->SetPos(sVector2<float>(100, 500));

	WFlag* flag = InstanceSpawn<WFlag>(eLayerType::Environment);
	WTransform* flagTransform = flag->GetComponent<WTransform>();
	WBoxCollider2D* BoxCollider = flag->AddComponent<WBoxCollider2D>();
	WFlagScript* FlagScript = flag->AddComponent<WFlagScript>();
	flagTransform->SetPos(sVector2<float>(5295, 80));
	BoxCollider->SetSize(sVector2<float>(20, 450));

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
	WColliderManager::SetColliderEnable(eLayerType::Player, eLayerType::Environment, true);
	WColliderManager::SetColliderEnable(eLayerType::Character, eLayerType::Environment, true);
	WColliderManager::SetColliderEnable(eLayerType::Item, eLayerType::Environment, true);

	WUIManager::Push(eUIType::HUD);
}

void Won::WPlayScene::OnExit()
{
	MainCamera = nullptr;
	WUIManager::Pop(eUIType::HUD);
	WColliderManager::Clear();
}
