// Window_Editor.cpp : Defines the entry point for the application.

#include "framework.h"
#include "WindowEditor.h"
#include "../WonEngineSource/WonApplication.h"
#include "../WonEngine/WonEngine/LoadScenes.h"
#include "../WonEngine/WonEngine/LoadResources.h"
#include "../WonEngineSource/WSceneManager.h"
#include <crtdbg.h>


#pragma comment(lib, "../WindowEditor/x64/Debug/WonEngine.lib")

Won::WonApplication Engine;

ULONG_PTR gpToken;
Gdiplus::GdiplusStartupInput gdsi;

#define MAX_LOADSTRING 100
#define _CRTDBG_MAP_ALLOC

HINSTANCE hInst;                               
WCHAR szTitle[MAX_LOADSTRING];                 
WCHAR szWindowClass[MAX_LOADSTRING];           

ATOM                MyRegisterClass(HINSTANCE hInstance,const wchar_t* Name, WNDPROC proc);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    //생성된 메모리에 Leak이 발생한 경우 알려줌.
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    
    //메모리 숫자를 넣으면 해당 순번에 생성된 메모리가 어디서 생성되었는지 알려줌.
    //_CrtSetBreakAlloc(22886);

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWEDITOR, szWindowClass, MAX_LOADSTRING);

    MyRegisterClass(hInstance, szWindowClass, WndProc);
    MyRegisterClass(hInstance, L"TILEMAP", WndProcToo);

    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWEDITOR));

    MSG msg;



    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                break;
            }
            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            Engine.Run();
        }

    }

    Engine.Release();
    Gdiplus::GdiplusShutdown(gpToken);

    return (int)msg.wParam;
}


ATOM MyRegisterClass(HINSTANCE hInstance,const wchar_t* Name, WNDPROC proc)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = proc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWEDITOR));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINDOWEDITOR);
    wcex.lpszClassName = Name;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance;

    const int Width = 774;
    const int Height = 729;

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        0, 0, Width, Height, nullptr, nullptr, hInstance, nullptr);

    Engine.Initialize(hWnd, Width, Height);

    if (!hWnd)
    {
        return FALSE;
    }


    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    Gdiplus::GdiplusStartup(&gpToken, &gdsi, NULL);
    Won::LoadResources();
    Won::LoadScenes();

    int a = 0;
    srand((unsigned int)(&a));

    if(Won::WSceneManager::GetActiveScene()->GetName() == L"ToolLevel")
    {
        HWND hWndToo = CreateWindowW(L"TILEMAP", L"TileMap", WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, 0, Width, Height, nullptr, nullptr, hInstance, nullptr);

        Won::WTexture* texture
            = Won::WResourceManager::Find<Won::WTexture>(L"Ob");

        RECT rect = { 0, 0, static_cast<int>(texture->GetWidth()), static_cast<int>(texture->GetHeight()) };
        AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

        UINT toolWidth = rect.right - rect.left;
        UINT toolHeight = rect.bottom - rect.top;

        SetWindowPos(hWndToo, nullptr, Width, 0, toolWidth, toolHeight, 0);
        ShowWindow(hWndToo, true);
        UpdateWindow(hWndToo);
    }

    return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
