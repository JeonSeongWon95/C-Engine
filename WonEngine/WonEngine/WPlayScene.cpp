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
	Vector2 SheetIndex;
	Vector2 TileIndex;

	while (!feof(Pfile))
	{
		fread(&SheetIndex, sizeof(SheetIndex), 1, Pfile);
		fread(&TileIndex, sizeof(TileIndex), 1, Pfile);
		TileObject* Object = InstanceSpawn<TileObject>(eLayerType::Tilemap);
		WTransform* ObjectTransform = Object->GetComponent<WTransform>();
		ObjectTransform->SetScale(Vector2(3.0f, 3.0f));
		WTileRenderer* TileRender = Object->AddComponent<WTileRenderer>();
		TileRender->SetTexture(WResourceManager::Find<WTexture>(L"Te"));
		ObjectTransform->SetPos(Vector2((TileIndex.x * TileRender->GetSize().x), (TileIndex.y * TileRender->GetSize().y)));
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
	floorTr->SetPos(Vector2(0, 575.0f));
	floorTr->SetScale(Vector2(1, 500));
	floorBx->SetSize(Vector2(2360.0f, 50.0f));

	Floor* floortwo = InstanceSpawn<Floor>(eLayerType::Environment);
	WTransform* floortwoTr = floortwo->GetComponent<WTransform>();
	floortwo->AddComponent<WFloorScript>();
	WBoxCollider2D* floortwoBx = floortwo->AddComponent<WBoxCollider2D>();
	floortwoTr->SetPos(Vector2(2450.0f, 575.0f));
	floortwoTr->SetScale(Vector2(1, 500));
	floortwoBx->SetSize(Vector2(480.0f, 50.0f));

	Floor* floorth = InstanceSpawn<Floor>(eLayerType::Environment);
	WTransform* floorthTr = floorth->GetComponent<WTransform>();
	floorth->AddComponent<WFloorScript>();
	WBoxCollider2D* floortrBx = floorth->AddComponent<WBoxCollider2D>();
	floorthTr->SetPos(Vector2(3025.0f, 575.0f));
	floorthTr->SetScale(Vector2(1, 500));
	floortrBx->SetSize(Vector2(810.0f, 50.0f));

	Floor* floorf = InstanceSpawn<Floor>(eLayerType::Environment);
	WTransform* floorfTr = floorf->GetComponent<WTransform>();
	floorf->AddComponent<WFloorScript>();
	WBoxCollider2D* floorfBx = floorf->AddComponent<WBoxCollider2D>();
	floorfTr->SetPos(Vector2(3940.0f, 575.0f));
	floorfTr->SetScale(Vector2(1, 500));
	floorfBx->SetSize(Vector2(310.0f, 50.0f));

	Floor* floorfive = InstanceSpawn<Floor>(eLayerType::Environment);
	WTransform* floorfiveTransform = floorfive->GetComponent<WTransform>();
	floorfive->AddComponent<WFloorScript>();
	WBoxCollider2D* floorfiveCollider = floorfive->AddComponent<WBoxCollider2D>();
	floorfiveTransform->SetPos(Vector2(4380.0f, 575.0f));
	floorfiveTransform->SetScale(Vector2(1, 500));
	floorfiveCollider->SetSize(Vector2(2000.0f, 50.0f));

	WWall* WallOne = InstanceSpawn<WWall>(eLayerType::Environment);
	WTransform* WallOneTransform = WallOne->GetComponent<WTransform>();
	WBoxCollider2D* WallOneCollider = WallOne->AddComponent<WBoxCollider2D>();
	WallOneTransform->SetPos(Vector2(1585.0f, 490.0f));
	WallOneCollider->SetSize(Vector2(85.0f, 100.0f));

	WWall* WallTwo = InstanceSpawn<WWall>(eLayerType::Environment);
	WTransform* WallTwoTransform = WallTwo->GetComponent<WTransform>();
	WBoxCollider2D* WallTwoCollider = WallTwo->AddComponent<WBoxCollider2D>();
	WallTwoTransform->SetPos(Vector2(1880.0f, 440.0f));
	WallTwoCollider->SetSize(Vector2(85.0f, 150.0f));

	WWall* WallThree = InstanceSpawn<WWall>(eLayerType::Environment);
	WTransform* WallThreeTransform = WallThree->GetComponent<WTransform>();
	WBoxCollider2D* WallThreeCollider = WallThree->AddComponent<WBoxCollider2D>();
	WallThreeTransform->SetPos(Vector2(2120.0f, 390.0f));
	WallThreeCollider->SetSize(Vector2(85.0f, 200.0f));

	WWall* WallFour = InstanceSpawn<WWall>(eLayerType::Environment);
	WTransform* WallFourTransform = WallFour->GetComponent<WTransform>();
	WBoxCollider2D* WallFourCollider = WallFour->AddComponent<WBoxCollider2D>();
	WallFourTransform->SetPos(Vector2(3165.0f, 530.0f));
	WallFourCollider->SetSize(Vector2(200.0f, 50.0f));

	WWall* WallFive = InstanceSpawn<WWall>(eLayerType::Environment);
	WTransform* WallFiveTransform = WallFive->GetComponent<WTransform>();
	WBoxCollider2D* WallFiveCollider = WallFive->AddComponent<WBoxCollider2D>();
	WallFiveTransform->SetPos(Vector2(3215.0f, 480.0f));
	WallFiveCollider->SetSize(Vector2(150.0f, 50.0f));

	WWall* WallSix = InstanceSpawn<WWall>(eLayerType::Environment);
	WTransform* WallSixTransform = WallSix->GetComponent<WTransform>();
	WBoxCollider2D* WallSixCollider = WallSix->AddComponent<WBoxCollider2D>();
	WallSixTransform->SetPos(Vector2(3265.0f, 430.0f));
	WallSixCollider->SetSize(Vector2(100.0f, 50.0f));

	WWall* WallSeven = InstanceSpawn<WWall>(eLayerType::Environment);
	WTransform* WallSevenransform = WallSeven->GetComponent<WTransform>();
	WBoxCollider2D* WallSevenCollider = WallSeven->AddComponent<WBoxCollider2D>();
	WallSevenransform->SetPos(Vector2(3315.0f, 380.0f));
	WallSevenCollider->SetSize(Vector2(50.0f, 50.0f));

	WWall* WallEight = InstanceSpawn<WWall>(eLayerType::Environment);
	WTransform* WallEightTransform = WallEight->GetComponent<WTransform>();
	WBoxCollider2D* WallEightCollider = WallEight->AddComponent<WBoxCollider2D>();
	WallEightTransform->SetPos(Vector2(3505.0f, 530.0f));
	WallEightCollider->SetSize(Vector2(150.0f, 50.0f));

	WWall* WallNine = InstanceSpawn<WWall>(eLayerType::Environment);
	WTransform* WallNineTransform = WallNine->GetComponent<WTransform>();
	WBoxCollider2D* WallNineCollider = WallNine->AddComponent<WBoxCollider2D>();
	WallNineTransform->SetPos(Vector2(3505.0f, 480.0f));
	WallNineCollider->SetSize(Vector2(100.0f, 50.0f));

	WWall* WallTen = InstanceSpawn<WWall>(eLayerType::Environment);
	WTransform* WallTenTransform = WallTen->GetComponent<WTransform>();
	WBoxCollider2D* WallTenCollider = WallTen->AddComponent<WBoxCollider2D>();
	WallTenTransform->SetPos(Vector2(3505.0f, 430.0f));
	WallTenCollider->SetSize(Vector2(50.0f, 50.0f));

	WWall* WallEleven = InstanceSpawn<WWall>(eLayerType::Environment);
	WTransform* WallElevenTransform = WallEleven->GetComponent<WTransform>();
	WBoxCollider2D* WallElevenCollider = WallEleven->AddComponent<WBoxCollider2D>();
	WallElevenTransform->SetPos(Vector2(3980.0f, 530.0f));
	WallElevenCollider->SetSize(Vector2(300.0f, 50.0f));

	WWall* Walltwelve = InstanceSpawn<WWall>(eLayerType::Environment);
	WTransform* WalltwelveTransform = Walltwelve->GetComponent<WTransform>();
	WBoxCollider2D* WalltwelveCollider = Walltwelve->AddComponent<WBoxCollider2D>();
	WalltwelveTransform->SetPos(Vector2(4650.0f, 540.0f));
	WalltwelveCollider->SetSize(Vector2(400.0f, 50.0f));

	WWall* WallThirteen = InstanceSpawn<WWall>(eLayerType::Environment);
	WTransform* WallThirteenTransform = WallThirteen->GetComponent<WTransform>();
	WBoxCollider2D* WallThirteenCollider = WallThirteen->AddComponent<WBoxCollider2D>();
	WallThirteenTransform->SetPos(Vector2(4700.0f, 490.0f));
	WallThirteenCollider->SetSize(Vector2(350.0f, 50.0f));

	WWall* WallFourteen = InstanceSpawn<WWall>(eLayerType::Environment);
	WTransform* WallFourteenTransform = WallFourteen->GetComponent<WTransform>();
	WBoxCollider2D* WallFourteenCollider = WallFourteen->AddComponent<WBoxCollider2D>();
	WallFourteenTransform->SetPos(Vector2(4750.0f, 440.0f));
	WallFourteenCollider->SetSize(Vector2(300.0f, 50.0f));

	WWall* Wallfifteen = InstanceSpawn<WWall>(eLayerType::Environment);
	WTransform* WallfifteenTransform = Wallfifteen->GetComponent<WTransform>();
	WBoxCollider2D* WallfifteenCollider = Wallfifteen->AddComponent<WBoxCollider2D>();
	WallfifteenTransform->SetPos(Vector2(4800.0f, 390.0f));
	WallfifteenCollider->SetSize(Vector2(250.0f, 50.0f));

	WWall* Wallsixteen = InstanceSpawn<WWall>(eLayerType::Environment);
	WTransform* WallsixteenTransform = Wallsixteen->GetComponent<WTransform>();
	WBoxCollider2D* WallsixteenCollider = Wallsixteen->AddComponent<WBoxCollider2D>();
	WallsixteenTransform->SetPos(Vector2(4850.0f, 340.0f));
	WallsixteenCollider->SetSize(Vector2(200.0f, 50.0f));

	WWall* Wallseventeen = InstanceSpawn<WWall>(eLayerType::Environment);
	WTransform* WallseventeenTransform = Wallseventeen->GetComponent<WTransform>();
	WBoxCollider2D* WallseventeenCollider = Wallseventeen->AddComponent<WBoxCollider2D>();
	WallseventeenTransform->SetPos(Vector2(4900.0f, 290.0f));
	WallseventeenCollider->SetSize(Vector2(150.0f, 50.0f));

	WWall* Walleighteen = InstanceSpawn<WWall>(eLayerType::Environment);
	WTransform* WalleighteenTransform = Walleighteen->GetComponent<WTransform>();
	WBoxCollider2D* WalleighteenCollider = Walleighteen->AddComponent<WBoxCollider2D>();
	WalleighteenTransform->SetPos(Vector2(4950.0f, 240.0f));
	WalleighteenCollider->SetSize(Vector2(100.0f, 50.0f));

	WFlagBlock* flagblock = InstanceSpawn<WFlagBlock>(eLayerType::Environment);
	WTransform* flagblockTransform = flagblock->GetComponent<WTransform>();
	WBoxCollider2D* flagblockCollider = flagblock->AddComponent<WBoxCollider2D>();
	flagblock->AddComponent<WFlagBlockScript>();
	flagblockTransform->SetPos(Vector2(5280.0f, 525.0f));
	flagblockCollider->SetSize(Vector2(50.0f, 50.0f));

	WGameObject* KingdomWall = InstanceSpawn<WGameObject>(eLayerType::Environment);
	WTransform* KingdomWallTransform = KingdomWall->GetComponent<WTransform>();
	WBoxCollider2D* KingdomWallCollider = KingdomWall->AddComponent<WBoxCollider2D>();
	KingdomWall->AddComponent<WEndScript>();
	KingdomWallTransform->SetPos(Vector2(5750.0f, 200.0f));
	KingdomWallCollider->SetSize(Vector2(10.0f, 400.0f));

	mCharacter = InstanceSpawn<Player>(eLayerType::Player);
	WPlayerScript* chScr = mCharacter->AddComponent<WPlayerScript>();
	WRigidbody* ChRg = mCharacter->AddComponent<WRigidbody>();
	ChRg->Setmass(1.5f);

	WBoxCollider2D* PlayerCollider = mCharacter->AddComponent<WBoxCollider2D>();
	PlayerCollider->SetSize(Vector2(50.0f, 50.0f));

	WTransform* CTR = mCharacter->GetComponent<WTransform>();
	CTR->SetScale(Vector2(3.0f, 3.0f));
	CTR->SetPos(Vector2(0, 500.f));

	WTexture* CharcterTexture = WResourceManager::Find<WTexture>(L"Ch");
	WAnimator* CAT = mCharacter->AddComponent<WAnimator>();

	CAT->CreateAnimation(L"RightWalk", CharcterTexture, Vector2(0, 7), Vector2(18.5, 16), Vector2(9.25, 16), 4, 0.1f);
	CAT->CreateAnimation(L"LeftWalk", CharcterTexture, Vector2(570, 221), Vector2(18.5, 16), Vector2(9.25, 16), 4, 0.1f, true);
	CAT->CreateAnimation(L"RightIdle", CharcterTexture, Vector2(0, 7), Vector2(18.5, 16), Vector2(9.25, 16), 1, 0.2f);
	CAT->CreateAnimation(L"LeftIdle", CharcterTexture, Vector2(570, 221), Vector2(18.5, 16),Vector2(9.25, 16), 1, 0.2f, true);
	CAT->CreateAnimation(L"ChangeToRightBigger", CharcterTexture, Vector2(18.5, 72), Vector2(18.5, 32), Vector2(9.25, 32), 2, 0.3f);
	CAT->CreateAnimation(L"ChangeToLeftBigger", CharcterTexture, Vector2(550.5, 285), Vector2(18.5, 32), Vector2(9.25, 32), 2, 0.3f, true);
	CAT->CreateAnimation(L"ChangeToRightSmall", CharcterTexture, Vector2(37, 72), Vector2(18.5, 32), Vector2(9.25, 32), 2, 0.3f, true);
	CAT->CreateAnimation(L"ChangeToLeftSmall", CharcterTexture, Vector2(532, 285), Vector2(18.5, 32), Vector2(9.25, 32), 2, 0.3f);
	CAT->CreateAnimation(L"BiggerRightWalk", CharcterTexture, Vector2(0, 32), Vector2(18.5, 32), Vector2(9.25, 32), 4, 0.1f);
	CAT->CreateAnimation(L"BiggerLeftWalk", CharcterTexture, Vector2(570, 246), Vector2(18.5, 32), Vector2(9.25, 32), 4, 0.1f, true);
	CAT->CreateAnimation(L"BiggerRightIdle", CharcterTexture, Vector2(0, 32), Vector2(18.5, 32), Vector2(9.25, 32), 1, 0.2f);
	CAT->CreateAnimation(L"BiggerLeftIdle", CharcterTexture, Vector2(570, 246), Vector2(18.5, 32), Vector2(9.25, 32), 1, 0.2f, true);
	CAT->CreateAnimation(L"Dead", CharcterTexture, Vector2(115, 7), Vector2(18.5, 16), Vector2(9.25, 32), 1, 0.2f);
	CAT->CreateAnimation(L"LeftJumpSmall", CharcterTexture, Vector2(475, 221), Vector2(18.5, 16), Vector2(9.25, 16), 1, 0.1f, true);
	CAT->CreateAnimation(L"RightJumpSmall", CharcterTexture, Vector2(96.5, 7), Vector2(18.5, 16), Vector2(9.25, 16), 1, 0.1f);
	CAT->CreateAnimation(L"LeftJumpBigger", CharcterTexture, Vector2(455, 246), Vector2(20, 32), Vector2(10, 32), 1, 0.1f);
	CAT->CreateAnimation(L"RightJumpBigger", CharcterTexture, Vector2(96.5, 32), Vector2(20, 32), Vector2(10, 32), 1, 0.1f);
	CAT->CreateAnimation(L"PickupflagBigger", CharcterTexture, Vector2(156.5, 32), Vector2(20, 32), Vector2(10, 32), 1, 0.1f);
	CAT->CreateAnimation(L"PickupflagSmall", CharcterTexture, Vector2(156.5, 7), Vector2(20, 16), Vector2(10, 32), 1, 0.1f);
	CAT->CreateAnimation(L"Attack", CharcterTexture,Vector2(135, 73), Vector2(20, 32), Vector2(10, 32), 1, 0.1f);
	CAT->GetStartEvent(L"Attack") = std::bind(&WPlayerScript::Fire, chScr);
	CAT->GetStartEvent(L"Dead") = std::bind(&WPlayerScript::Dead, chScr);
	CAT->PlayAnimation(L"RightIdle", false);

	Enemy* Monster = InstanceSpawn<Enemy>(eLayerType::Character);
	WTransform* MonsterTransform = Monster->GetComponent<WTransform>();
	MonsterTransform->SetScale(Vector2(3.0f, 3.0f));
	MonsterTransform->SetPos(Vector2(500.f, 500.f));

	Enemy* Monsterfour = InstanceSpawn<Enemy>(eLayerType::Character);
	WTransform* MonsterfourTransform = Monsterfour->GetComponent<WTransform>();
	MonsterfourTransform->SetScale(Vector2(3.0f, 3.0f));
	MonsterfourTransform->SetPos(Vector2(650.f, 500.f));

	Enemy* Monstertwo = InstanceSpawn<Enemy>(eLayerType::Character);
	WTransform* MonstertwoTransform = Monstertwo->GetComponent<WTransform>();
	MonstertwoTransform->SetScale(Vector2(3.0f, 3.0f));
	MonstertwoTransform->SetPos(Vector2(750.f, 500.f));

	Enemy* Monsterthree = InstanceSpawn<Enemy>(eLayerType::Character);
	WTransform* MonsterthreeTransform = Monsterthree->GetComponent<WTransform>();
	MonsterthreeTransform->SetScale(Vector2(3.0f, 3.0f));
	MonsterthreeTransform->SetPos(Vector2(800.f, 500.f));

	ItemBlock* Itemblock = InstanceSpawn<ItemBlock>(eLayerType::Environment);
	WTransform* ItemblockTransform = Itemblock->GetComponent<WTransform>();
	ItemblockTransform->SetScale(Vector2(3.0f, 3.0f));
	ItemblockTransform->SetPos(Vector2(300, 300));

	Block* block = InstanceSpawn<Block>(eLayerType::Environment);
	WTransform* blockTransform = block->GetComponent<WTransform>();
	blockTransform->SetScale(Vector2(3.0f, 3.0f));
	blockTransform->SetPos(Vector2(200, 400));

	Block* blocka = InstanceSpawn<Block>(eLayerType::Environment);
	WTransform* blockaTransform = blocka->GetComponent<WTransform>();
	blockaTransform->SetScale(Vector2(3.0f, 3.0f));
	blockaTransform->SetPos(Vector2(1000, 400));
	Block* blockb = InstanceSpawn<Block>(eLayerType::Environment);
	WTransform* blockbTransform = blockb->GetComponent<WTransform>();
	blockbTransform->SetScale(Vector2(3.0f, 3.0f));
	blockbTransform->SetPos(Vector2(1050, 400));
	Block* blockc = InstanceSpawn<Block>(eLayerType::Environment);
	WTransform* blockcTransform = blockc->GetComponent<WTransform>();
	blockcTransform->SetScale(Vector2(3.0f, 3.0f));
	blockcTransform->SetPos(Vector2(1100, 400));
	Block* blockd = InstanceSpawn<Block>(eLayerType::Environment);
	WTransform* blockdTransform = blockd->GetComponent<WTransform>();
	blockdTransform->SetScale(Vector2(3.0f, 3.0f));
	blockdTransform->SetPos(Vector2(1150, 400));

	Block* blocke = InstanceSpawn<Block>(eLayerType::Environment);
	WTransform* blockeTransform = blocke->GetComponent<WTransform>();
	blockeTransform->SetScale(Vector2(3.0f, 3.0f));
	blockeTransform->SetPos(Vector2(3125, 200));
	Block* blockf = InstanceSpawn<Block>(eLayerType::Environment);
	WTransform* blockfTransform = blockf->GetComponent<WTransform>();
	blockfTransform->SetScale(Vector2(3.0f, 3.0f));
	blockfTransform->SetPos(Vector2(3175, 200));
	Block* blockg = InstanceSpawn<Block>(eLayerType::Environment);
	WTransform* blockgTransform = blockg->GetComponent<WTransform>();
	blockgTransform->SetScale(Vector2(3.0f, 3.0f));
	blockgTransform->SetPos(Vector2(3600, 200));
	Block* blockh = InstanceSpawn<Block>(eLayerType::Environment);
	WTransform* blockhTransform = blockh->GetComponent<WTransform>();
	blockhTransform->SetScale(Vector2(3.0f, 3.0f));
	blockhTransform->SetPos(Vector2(3850, 200));

	Coin* coin = InstanceSpawn<Coin>(eLayerType::Item);
	WTransform* coinTransform = coin->GetComponent<WTransform>();
	coinTransform->SetScale(Vector2(3.0f, 3.0f));
	coinTransform->SetPos(Vector2(100, 500));

	WFlag* flag = InstanceSpawn<WFlag>(eLayerType::Environment);
	WTransform* flagTransform = flag->GetComponent<WTransform>();
	WBoxCollider2D* BoxCollider = flag->AddComponent<WBoxCollider2D>();
	WFlagScript* FlagScript = flag->AddComponent<WFlagScript>();
	flagTransform->SetPos(Vector2(5295, 80));
	BoxCollider->SetSize(Vector2(20, 450));

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
