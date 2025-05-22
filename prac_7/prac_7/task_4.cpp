// prac_spider.cpp : ���������� ����� ����� ��� ����������.
//

#include "framework.h"
#include "prac_spider.h"
#include <windows.h>
#include <math.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#define MAX_LOADSTRING 100

// ���������� ����������:
HINSTANCE hInst;                                // ������� ���������
WCHAR szTitle[MAX_LOADSTRING];                  // ����� ������ ���������
WCHAR szWindowClass[MAX_LOADSTRING];            // ��� ������ �������� ����

// ���������� ��� "������"
POINT spiderPos = { 0, 0 };
POINT spiderVel = { 0, 0 };
bool spiderVisible = false;
HBITMAP hSpiderBitmap = nullptr;
SIZE spiderSize = { 64, 64 }; // ������ ����������� "������"

// ������������� �������
#define IDT_TIMER1 1

// ��������� ���������� �������, ���������� � ���� ������ ����:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// ������� �������� ����������� "������"
HBITMAP LoadSpiderBitmap()
{
    // �������� ����������� �� �������� ��� �����
    // ����� ����� ������������ LoadImage ��� ������ ������� ��������
    // ������:
    return (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(IDB_SPIDER), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR);
}

// ������� ��������������� ����� ��� ������������
void PlayCollisionSound()
{
    // ��������������� ���������� �����
    MessageBeep(MB_OK);
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // ������������� ���������� �����
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PRACSPIDER, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // ��������� ������������� ����������:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PRACSPIDER));

    MSG msg;

    // ���� ��������� ���������:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PRACSPIDER));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_PRACSPIDER);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // ��������� ������ ���������� � ���������� ����������

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, 800, 600, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

void UpdateSpiderPosition(HWND hWnd)
{
    RECT rect;
    GetClientRect(hWnd, &rect);

    // ���������� �������
    spiderPos.x += spiderVel.x;
    spiderPos.y += spiderVel.y;

    // �������� ������������ � ���������
    bool collided = false;
    if (spiderPos.x < 0)
    {
        spiderPos.x = 0;
        spiderVel.x = -spiderVel.x;
        collided = true;
    }
    else if (spiderPos.x + spiderSize.cx > rect.right)
    {
        spiderPos.x = rect.right - spiderSize.cx;
        spiderVel.x = -spiderVel.x;
        collided = true;
    }

    if (spiderPos.y < 0)
    {
        spiderPos.y = 0;
        spiderVel.y = -spiderVel.y;
        collided = true;
    }
    else if (spiderPos.y + spiderSize.cy > rect.bottom)
    {
        spiderPos.y = rect.bottom - spiderSize.cy;
        spiderVel.y = -spiderVel.y;
        collided = true;
    }

    if (collided)
    {
        PlayCollisionSound();
    }

    InvalidateRect(hWnd, nullptr, TRUE);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        // �������� ����������� "������"
        hSpiderBitmap = LoadSpiderBitmap();
    }
    break;
    case WM_LBUTTONDOWN:
    {
        // ������ �������� "������"
        spiderPos.x = LOWORD(lParam);
        spiderPos.y = HIWORD(lParam);
        spiderVel.x = 10;
        spiderVel.y = 10;
        spiderVisible = true;
        SetTimer(hWnd, IDT_TIMER1, 30, nullptr);
    }
    break;
    case WM_MOUSEMOVE:
    {
        // ���������� �������� ��� ����������� ����
        if (spiderVisible)
        {
            if (spiderVel.x > 0) spiderVel.x--;
            else if (spiderVel.x <= 0) spiderVel.x++;

            if (spiderVel.y > 0) spiderVel.y--;
            else if (spiderVel.y <= 0) spiderVel.y++;
        }
    }
    break;
    case WM_RBUTTONDOWN:
    {
        // ��������� � ������� "������"
        spiderVisible = false;
        KillTimer(hWnd, IDT_TIMER1);
        InvalidateRect(hWnd, nullptr, TRUE);
    }
    break;
    case WM_TIMER:
    {
        if (wParam == IDT_TIMER1 && spiderVisible)
        {
            UpdateSpiderPosition(hWnd);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        if (spiderVisible && hSpiderBitmap)
        {
            HDC hMemDC = CreateCompatibleDC(hdc);
            HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemDC, hSpiderBitmap);

            BitBlt(hdc, spiderPos.x, spiderPos.y, spiderSize.cx, spiderSize.cy, hMemDC, 0, 0, SRCCOPY);

            SelectObject(hMemDC, hOldBitmap);
            DeleteDC(hMemDC);
        }

        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
    {
        if (hSpiderBitmap)
        {
            DeleteObject(hSpiderBitmap);
        }
        PostQuitMessage(0);
    }
    break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
