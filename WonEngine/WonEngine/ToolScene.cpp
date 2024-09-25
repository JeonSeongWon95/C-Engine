#include "ToolScene.h"
#include "WonObject.h"
#include "TileObject.h"
#include "TileRenderer.h"
#include "ResourceManager.h"
#include "WTexture.h"
#include "Input.h"
#include "WCamera.h"
#include "WCameraScript.h"
#include "WRender.h"

Won::mVector2<int> Won::ToolScene::sStartPosition = Won::mVector2<int>(-1,-1);

Won::ToolScene::ToolScene()
{
}

Won::ToolScene::~ToolScene()
{
}

void Won::ToolScene::Initialize()
{
	GameObject* Camera = InstanceSpawn<GameObject>(eLayerType::None);
	WCamera* CameraComponent =	Camera->AddComponent<WCamera>();
	Camera->AddComponent<WCameraScript>();

	MainCamera = CameraComponent;

	Scene_Level::Initialize();
}

void Won::ToolScene::Update()
{
	Scene_Level::Update();

	if (Input::GetKey(KeyType::LBUTTON))
	{

		mVector2<float> pos = Input::GetMousePosition();
		pos = MainCamera->CaluateTilePosition(pos);

		if (pos.X >= 0.0f && pos.Y >= 0.0f)
		{

			mVector2 <float> MousePos = Input::GetMousePosition();
			TileObject* Object = InstanceSpawn<TileObject>(eLayerType::Tilemap);

			Transform* ObjectTransform = Object->GetComponent<Transform>();
			ObjectTransform->SetScale(mVector2<float>(3.0f, 3.0f));

			TileRenderer* TileRender = Object->AddComponent<TileRenderer>();
			TileRender->SetTexture(ResourceManager::Find<WTexture>(L"Ob"));

			mVector2<float> Size = TileRender->GetSize();
			mVector2<float> Scale = ObjectTransform->GetScale();
			mVector2<int> Index;
			mVector2<float> Position;
			Index.X = static_cast<int>(MousePos.X / (Size.X * Scale.X));
			Index.Y = static_cast<int>(MousePos.Y / (Size.Y * Scale.Y));

			Position.X = Index.X * (Size.X * Scale.X);
			Position.Y = Index.Y * (Size.Y * Scale.Y);

			ObjectTransform->SetPos(Position);
			TileRender->SetSheetIndex(sStartPosition);
		}
	}
}

void Won::ToolScene::LateUpdate()
{
	Scene_Level::LateUpdate();

	if(Input::GetKey(KeyType::S))
	{
		Save();
	}
	else if(Input::GetKey(KeyType::L))
	{
		Load();
	}
}

void Won::ToolScene::Render(HDC NewDC)
{
	Scene_Level::Render(NewDC);

	for (int i = 0; i < 50; ++i)
	{
		mVector2<float> Pos = MainCamera->CaluatePostion(mVector2<float>((16 * 3 * i), 0));

		MoveToEx(NewDC, Pos.X, 0, NULL);
		LineTo(NewDC, Pos.X, 1000);
	}
	for (int i = 0; i < 50; ++i)
	{
		mVector2<float> Pos = MainCamera->CaluatePostion(mVector2<float>(0, (16 * 3 * i)));

		MoveToEx(NewDC, 0, Pos.Y, NULL);
		LineTo(NewDC, 1000, Pos.Y);
	}
}

void Won::ToolScene::OnEnter()
{
}

void Won::ToolScene::OnExit()
{
}

void Won::ToolScene::Load()
{
	OPENFILENAME ofn = {};

	wchar_t szFilePath[256] = {};

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFilePath;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 256;
	ofn.lpstrFilter = L"All\0*.*\0Text\0*.TXT\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (FALSE == GetSaveFileName(&ofn))
		return;

	FILE* Pfile = nullptr;
	_wfopen_s(&Pfile, szFilePath, L"rb");

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
}

void Won::ToolScene::Save()
{
	OPENFILENAME ofn = {};

	wchar_t szFilePath[256] = {};

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFilePath;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 256;
	ofn.lpstrFilter = L"Tile\0*.tile\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (FALSE == GetSaveFileName(&ofn))
		return;


	FILE* Pfile = nullptr;
	_wfopen_s(&Pfile, szFilePath, L"wb");

	if (Pfile == nullptr)
		return;

	WLayer* TileLayers = Scene_Level::GetLayer(eLayerType::Tilemap);

	mVector2<int> SheetIndex;
	mVector2<int> TileIndex;

	for(GameObject* GB : TileLayers->GetGameObject())
	{
		if (GB->GetComponent<TileRenderer>() == nullptr)
			continue;
		
		TileRenderer* TileRender = GB->GetComponent<TileRenderer>();
		Transform* ObjectTransform = GB->GetComponent<Transform>();
		TileIndex.X = ObjectTransform->GetPosition().X / TileRender->GetSize().X;
		TileIndex.Y = ObjectTransform->GetPosition().Y / TileRender->GetSize().Y;
		SheetIndex.X = TileRender->GetSheetIndex().X;
		SheetIndex.Y = TileRender->GetSheetIndex().Y;

		fwrite(&SheetIndex, sizeof(SheetIndex), 1, Pfile);
		fwrite(&TileIndex, sizeof(TileIndex), 1, Pfile);
		
	}

	fclose(Pfile);
}

LRESULT CALLBACK WndProcToo(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	Won::mVector2<int> mStartPosition = Won::mVector2<int>(0, 0);
	Won::mVector2<int> SheetIndex = Won::mVector2<int>(0, 0);
	Won::mVector2 <float> MousePos = Won::mVector2<float>(0, 0);
	POINT Cursorpos = {};

    switch (message)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: Add any drawing code that uses hdc here...
        Won::WTexture* Image = Won::ResourceManager::Find<Won::WTexture>(L"Ob");

        TransparentBlt(hdc
            , 0
            , 0
            , static_cast<int>(Image->GetWidth())
            , static_cast<int>(Image->GetHeight())
            , Image->GetHDC()
            , 0
            , 0
            , Image->GetWidth()
            , Image->GetHeight()
            , RGB(255, 0, 255));

		for (int i = 0; i < 50; ++i)
		{
			MoveToEx(hdc, 16 * i, 0, NULL);
			LineTo(hdc, 16 * i, 1000);
		}
		for (int i = 0; i < 50; ++i)
		{
			MoveToEx(hdc, 0, 16 * i, NULL);
			LineTo(hdc, 1000, 16 * i);
		}


        EndPaint(hWnd, &ps);
    }
    break;

	case WM_LBUTTONDOWN:
		
		GetCursorPos(&Cursorpos);
		ScreenToClient(hWnd, &Cursorpos);

		MousePos.X = Cursorpos.x;
		MousePos.Y = Cursorpos.y;

		mStartPosition.X = static_cast<int>(MousePos.X / 16);
		mStartPosition.Y = static_cast<int>(MousePos.Y / 16);

		Won::ToolScene::sStartPosition = mStartPosition;
		break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
