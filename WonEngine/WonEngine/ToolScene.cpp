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

Won::Vector2 Won::ToolScene::sStartPosition = Won::Vector2(-1,-1);
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
		Vector2 MousePos = WInput::GetMousePosition();

		if (MousePos.x == -1 && MousePos.y == -1 || sStartPosition.x == -1 || sStartPosition.y == -1)
			return;

		MousePos = MainCamera->CaluateTilePosition(MousePos);

		if (MousePos.x >= 0.0f && MousePos.y >= 0.0f)
		{

			TileObject* Object = InstanceSpawn<TileObject>(eLayerType::Tilemap);

			WTransform* ObjectTransform = Object->GetComponent<WTransform>();
			ObjectTransform->SetScale(Vector2(3.0f, 3.0f));

			WTileRenderer* TileRender = Object->AddComponent<WTileRenderer>();
			TileRender->SetTexture(WResourceManager::Find<WTexture>(L"Te"));

			Vector2 Size = TileRender->GetSize();
			Vector2 Scale = ObjectTransform->GetScale();
			Vector2 Index;
			Vector2 Position;
			Index.x = static_cast<int>(MousePos.x / (Size.x * Scale.x));
			Index.y = static_cast<int>(MousePos.y / (Size.y * Scale.y));

			Position.x = Index.x * (Size.x * Scale.x);
			Position.y = Index.y * (Size.y * Scale.y);

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
		Vector2 Pos = MainCamera->CaluatePostion(Vector2(static_cast<float>((16 * 3 * i)), 0));

		MoveToEx(NewDC, static_cast<int>(Pos.x), 0, NULL);
		LineTo(NewDC, static_cast<int>(Pos.x), 1000);
	}
	for (int i = 0; i < 50; ++i)
	{
		Vector2 Pos = MainCamera->CaluatePostion(Vector2(0, (static_cast<float>(16 * 3 * i))));

		MoveToEx(NewDC, 0, static_cast<int>(Pos.y), NULL);
		LineTo(NewDC, 1000, static_cast<int>(Pos.y));
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

	Vector2 SheetIndex;
	Vector2 TileIndex;

	for(WGameObject* GB : TileLayers->GetGameObject())
	{
		if (GB->GetComponent<WTileRenderer>() == nullptr)
			continue;
		
		WTileRenderer* TileRender = GB->GetComponent<WTileRenderer>();
		WTransform* ObjectTransform = GB->GetComponent<WTransform>();
		TileIndex.x = static_cast<int>(ObjectTransform->GetPosition().x / TileRender->GetSize().x);
		TileIndex.y = static_cast<int>(ObjectTransform->GetPosition().y / TileRender->GetSize().y);
		SheetIndex.x = TileRender->GetSheetIndex().x;
		SheetIndex.y = TileRender->GetSheetIndex().y;

		fwrite(&SheetIndex, sizeof(SheetIndex), 1, Pfile);
		fwrite(&TileIndex, sizeof(TileIndex), 1, Pfile);
		
	}

	fclose(Pfile);
}

LRESULT CALLBACK WndProcToo(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	Won::Vector2 mStartPosition = Won::Vector2(0, 0);
	Won::Vector2 SheetIndex = Won::Vector2(0, 0);
	Won::Vector2 MousePos = Won::Vector2(0, 0);
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

		MousePos.x = static_cast<float>(Cursorpos.x);
		MousePos.y = static_cast<float>(Cursorpos.y);

		mStartPosition.x = static_cast<int>(MousePos.x / 16);
		mStartPosition.y = static_cast<int>(MousePos.y / 16);

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
