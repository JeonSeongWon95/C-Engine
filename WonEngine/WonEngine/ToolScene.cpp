#include "ToolScene.h"
#include "WonObject.h"
#include "TileObject.h"
#include "WTileRenderer.h"
#include "WResourceManager.h"
#include "WTexture.h"
#include "WInput.h"
#include "WCamera.h"
#include "WCameraScript.h"
#include "WRender.h"
#include "WonApplication.h"

Won::sVector2<int> Won::ToolScene::sStartPosition = Won::sVector2<int>(-1,-1);
extern Won::WonApplication Engine;

Won::ToolScene::ToolScene()
{
}

Won::ToolScene::~ToolScene()
{
}

void Won::ToolScene::Initialize()
{
	WGameObject* Camera = InstanceSpawn<WGameObject>(eLayerType::None);
	WCamera* CameraComponent =	Camera->AddComponent<WCamera>();
	Camera->AddComponent<WCameraScript>();

	MainCamera = CameraComponent;
	WScene::Initialize();
}

void Won::ToolScene::Update()
{
	WScene::Update();

	HWND ActiveWindow = GetForegroundWindow();

	if (ActiveWindow != Engine.GetEngineWND())
		return;

	if (WInput::GetKey(KeyType::LBUTTON))
	{
		sVector2<float> MousePos = WInput::GetMousePosition();

		if (MousePos.X == -1 && MousePos.Y == -1 || sStartPosition.X == -1 || sStartPosition.Y == -1)
			return;

		MousePos = MainCamera->CaluateTilePosition(MousePos);

		if (MousePos.X >= 0.0f && MousePos.Y >= 0.0f)
		{

			TileObject* Object = InstanceSpawn<TileObject>(eLayerType::Tilemap);

			WTransform* ObjectTransform = Object->GetComponent<WTransform>();
			ObjectTransform->SetScale(sVector2<float>(3.0f, 3.0f));

			WTileRenderer* TileRender = Object->AddComponent<WTileRenderer>();
			TileRender->SetTexture(WResourceManager::Find<WTexture>(L"Te"));

			sVector2<float> Size = TileRender->GetSize();
			sVector2<float> Scale = ObjectTransform->GetScale();
			sVector2<int> Index;
			sVector2<float> Position;
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
	WScene::LateUpdate();

	if(WInput::GetKey(KeyType::S))
	{
		Save();
	}
	else if(WInput::GetKey(KeyType::L))
	{
		Load();
	}
}

void Won::ToolScene::Render(HDC NewDC)
{
	WScene::Render(NewDC);

	for (int i = 0; i < 50; ++i)
	{
		sVector2<float> Pos = MainCamera->CaluatePostion(sVector2<float>(static_cast<float>((16 * 3 * i)), 0));

		MoveToEx(NewDC, static_cast<int>(Pos.X), 0, NULL);
		LineTo(NewDC, static_cast<int>(Pos.X), 1000);
	}
	for (int i = 0; i < 50; ++i)
	{
		sVector2<float> Pos = MainCamera->CaluatePostion(sVector2<float>(0, (static_cast<float>(16 * 3 * i))));

		MoveToEx(NewDC, 0, static_cast<int>(Pos.Y), NULL);
		LineTo(NewDC, 1000, static_cast<int>(Pos.Y));
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

	WLayer* TileLayers = WScene::GetLayer(eLayerType::Tilemap);

	sVector2<int> SheetIndex;
	sVector2<int> TileIndex;

	for(WGameObject* GB : TileLayers->GetGameObject())
	{
		if (GB->GetComponent<WTileRenderer>() == nullptr)
			continue;
		
		WTileRenderer* TileRender = GB->GetComponent<WTileRenderer>();
		WTransform* ObjectTransform = GB->GetComponent<WTransform>();
		TileIndex.X = static_cast<int>(ObjectTransform->GetPosition().X / TileRender->GetSize().X);
		TileIndex.Y = static_cast<int>(ObjectTransform->GetPosition().Y / TileRender->GetSize().Y);
		SheetIndex.X = TileRender->GetSheetIndex().X;
		SheetIndex.Y = TileRender->GetSheetIndex().Y;

		fwrite(&SheetIndex, sizeof(SheetIndex), 1, Pfile);
		fwrite(&TileIndex, sizeof(TileIndex), 1, Pfile);
		
	}

	fclose(Pfile);
}

LRESULT CALLBACK WndProcToo(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	Won::sVector2<int> mStartPosition = Won::sVector2<int>(0, 0);
	Won::sVector2<int> SheetIndex = Won::sVector2<int>(0, 0);
	Won::sVector2 <float> MousePos = Won::sVector2<float>(0, 0);
	POINT Cursorpos = {};

    switch (message)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: Add any drawing code that uses hdc here...
        Won::WTexture* Image = Won::WResourceManager::Find<Won::WTexture>(L"Te");

		if (Image->IsAlpha())
		{
			BLENDFUNCTION func = {};
			func.BlendOp = AC_SRC_OVER;
			func.BlendFlags = 0;
			func.AlphaFormat = AC_SRC_ALPHA;
			func.SourceConstantAlpha = 255;


			AlphaBlend(hdc
				, 0
				, 0
				, static_cast<int>(Image->GetWidth())
				, static_cast<int>(Image->GetHeight())
				, Image->GetHDC()
				, 0
				, 0
				, Image->GetWidth()
				, Image->GetHeight(), func);
		}
		else
		{

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
		}

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

		MousePos.X = static_cast<float>(Cursorpos.x);
		MousePos.Y = static_cast<float>(Cursorpos.y);

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
