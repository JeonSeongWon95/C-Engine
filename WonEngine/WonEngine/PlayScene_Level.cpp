#include "PlayScene_Level.h"
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

Won::PlayScene_Level::PlayScene_Level()
{
}

Won::PlayScene_Level::~PlayScene_Level()
{
}
 
void Won::PlayScene_Level::Initialize()
{

	//FILE* Pfile = nullptr;
	//_wfopen_s(&Pfile, L"../Test", L"rb");

	//if (Pfile == nullptr)
	//	return;

	//sVector2<int> SheetIndex;
	//sVector2<int> TileIndex;

	//while (!feof(Pfile))
	//{

	//	fread(&SheetIndex, sizeof(SheetIndex), 1, Pfile);
	//	fread(&TileIndex, sizeof(TileIndex), 1, Pfile);

	//	TileObject* Object = InstanceSpawn<TileObject>(eLayerType::Tilemap);
	//	WTransform* ObjectTransform = Object->GetComponent<WTransform>();
	//	ObjectTransform->SetScale(sVector2<float>(3.0f, 3.0f));
	//	WTileRenderer* TileRender = Object->AddComponent<WTileRenderer>();
	//	TileRender->SetTexture(WResourceManager::Find<WTexture>(L"Ob"));
	//	ObjectTransform->SetPos(sVector2<float>((TileIndex.X * TileRender->GetSize().X), (TileIndex.Y * TileRender->GetSize().Y)));
	//	TileRender->SetSheetIndex(SheetIndex);

	//}

	//fclose(Pfile);

	//Player* BG = InstanceSpawn<Player>(eLayerType::BackGround);
	//WSpriteRenderComponent* BSRC = BG->AddComponent<WSpriteRenderComponent>();
	//BSRC->SetTexture(WResourceManager::Find<WTexture>(L"Ti"));
	//BSRC->SetSize(mVector2<float>(4.0f, 4.0f));
	//BSRC->SetStartPosition(mVector2<float>(0, -325));

	//Player* Effect = InstanceSpawn<Player>(eLayerType::Effect);
	//WTexture* EffectTexture = WResourceManager::Find<WTexture>(L"Ef");
	//WAnimator* CATS = Effect->AddComponent<WAnimator>();
	//CATS->CreateAnimation(L"Attack", EffectTexture, mVector2<float>(0, 0), mVector2<float>(200, 322), mVector2<float>(0, 0), 10, 0.1f);
	//CATS->PlayAnimation(L"Attack", true);
	//CATS->SetRemoveColor(mVector3<int>(0, 0, 0));

	Floor* floor = InstanceSpawn<Floor>(eLayerType::Floor);
	WTransform* floorTr = floor->GetComponent<WTransform>();
	floor->AddComponent<WFloorScript>();
	WBoxCollider2D* floorBx = floor->AddComponent<WBoxCollider2D>();
	floorTr->SetPos(sVector2<float>(0, 550.0f));
	floorTr->SetScale(sVector2<float>(1, 500));
	floorBx->SetSize(sVector2<float>(1000.0f, 50.0f));


	Player* Ch = InstanceSpawn<Player>(eLayerType::Player);
	WPlayerScript* chScr =  Ch->AddComponent<WPlayerScript>();
	WRigidbody* ChRg = Ch->AddComponent<WRigidbody>();
	ChRg->Setmass(1.5f);

	WBoxCollider2D* PlayerCollider = Ch->AddComponent<WBoxCollider2D>();
	//PlayerCollider->Setoffset(sVector2<float>(-18.0f, -25.0f));
	PlayerCollider->SetSize(sVector2<float>(50.0f, 50.0f));

	WTransform* CTR = Ch->GetComponent<WTransform>();
	CTR->SetScale(sVector2<float>(3.0f, 3.0f));
	CTR->SetPos(sVector2<float>(0, 500.f));

	WTexture* CharcterTexture = WResourceManager::Find<WTexture>(L"Ch");
	WAnimator* CAT = Ch->AddComponent<WAnimator>();

	CAT->CreateAnimation(L"RightWalk", CharcterTexture, sVector2<float>(0, 7), sVector2<float>(18.5, 16), sVector2<float>(9.25, 16), 4, 0.1f);
	CAT->CreateAnimation(L"LeftWalk", CharcterTexture, sVector2<float>(570, 221), sVector2<float>(18.5, 16), sVector2<float>(9.25, 16), 4, 0.1f, true);
	CAT->CreateAnimation(L"RightIdle", CharcterTexture, sVector2<float>(0, 7), sVector2<float>(18.5, 16), sVector2<float>(9.25, 16), 1, 0.2f);
	CAT->CreateAnimation(L"LeftIdle", CharcterTexture, sVector2<float>(570, 221), sVector2<float>(18.5, 16), sVector2<float>(9.25, 16), 1, 0.2f, true);
	CAT->CreateAnimation(L"ChangeToRightBigger", CharcterTexture, sVector2<float>(18.5, 73), sVector2<float>(18.5, 32), sVector2<float>(9.25, 32), 2, 0.1f);
	CAT->CreateAnimation(L"ChangeToLeftBigger", CharcterTexture, sVector2<float>(550.5, 286), sVector2<float>(18.5, 32), sVector2<float>(9.25, 32), 2, 0.1f, true);
	CAT->CreateAnimation(L"ChangeToRightSmall", CharcterTexture, sVector2<float>(37, 73), sVector2<float>(18.5, 32), sVector2<float>(9.25, 32), 2, 0.1f, true);
	CAT->CreateAnimation(L"ChangeToLeftSmall", CharcterTexture, sVector2<float>(532, 286), sVector2<float>(18.5, 32), sVector2<float>(9.25, 32), 2, 0.1f);
	CAT->CreateAnimation(L"BiggerRightWalk", CharcterTexture, sVector2<float>(0, 33), sVector2<float>(18.5, 32), sVector2<float>(9.25, 32), 4, 0.1f);
	CAT->CreateAnimation(L"BiggerLeftWalk", CharcterTexture, sVector2<float>(570, 247), sVector2<float>(18.5, 32), sVector2<float>(9.25, 32), 4, 0.1f, true);
	CAT->CreateAnimation(L"BiggerRightIdle", CharcterTexture, sVector2<float>(0, 33), sVector2<float>(18.5, 32), sVector2<float>(9.25, 32), 1, 0.2f);
	CAT->CreateAnimation(L"BiggerLeftIdle", CharcterTexture, sVector2<float>(570, 247), sVector2<float>(18.5, 32), sVector2<float>(9.25, 32), 1, 0.2f, true);
	CAT->CreateAnimation(L"Dead", CharcterTexture, sVector2<float>(111, 7), sVector2<float>(18.5, 16), sVector2<float>(9.25, 32), 1, 0.2f);
	CAT->CreateAnimation(L"Attack", CharcterTexture, sVector2<float>(135, 73), sVector2<float>(20, 32), sVector2<float>(10, 32), 1, 0.1f);
	CAT->GetStartEvent(L"Attack") = std::bind(&WPlayerScript::Fire, chScr);
	CAT->GetStartEvent(L"Dead") = std::bind(&WPlayerScript::Dead, chScr);
	CAT->PlayAnimation(L"RightIdle", false);

	//DestoryOnLoadScene(Ch);

	Enemy* Monster = InstanceSpawn<Enemy>(eLayerType::Character);
	WEnemyScript* MonsterScript = Monster->AddComponent<WEnemyScript>();

	WBoxCollider2D* MB = Monster->AddComponent<WBoxCollider2D>();
	MB->SetSize(sVector2<float>(50.0f, 50.0f));

	WTransform* MTR = Monster->GetComponent<WTransform>();
	MTR->SetScale(sVector2<float>(3.0f, 3.0f));
	MTR->SetPos(sVector2<float>(500.f, 500.f));

	WTexture* MonsterTexture = WResourceManager::Find<WTexture>(L"Ee");
	WAnimator* MAT = Monster->AddComponent<WAnimator>();
	MAT->CreateAnimation(L"Walk", MonsterTexture, sVector2<float>(0, 15), sVector2<float>(18.5, 18), sVector2<float>(0, 0), 2, 0.1f);
	MAT->CreateAnimation(L"Dead", MonsterTexture, sVector2<float>(37, 15), sVector2<float>(18.5, 18), sVector2<float>(0, 0), 1, 0.1f);
	MAT->GetCompleteEvent(L"Dead") = std::bind(&WEnemyScript::Dead, MonsterScript);
	MAT->PlayAnimation(L"Walk", true);

	WScene::Initialize();
}

void Won::PlayScene_Level::Update()
{
	WScene::Update();

	//if(WInput::GetKey(KeyType::A))
	//{
	//	WSceneManager::LoadScene(L"TitleLevel");
	//}
}

void Won::PlayScene_Level::LateUpdate()
{
	WScene::LateUpdate();
}

void Won::PlayScene_Level::Render(HDC NewDC)
{
	WScene::Render(NewDC);
}

void Won::PlayScene_Level::OnEnter()
{
	WColliderManager::SetColliderEnable(eLayerType::Player, eLayerType::Character, true);
	WColliderManager::SetColliderEnable(eLayerType::Player, eLayerType::Floor, true);

	//WUIManager::Push(eUIType::Button);
}

void Won::PlayScene_Level::OnExit()
{
	WColliderManager::Clear();
	//WUIManager::Pop(eUIType::Button);
}
