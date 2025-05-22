// prac_7.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "prac_7.h"
#include <utility>
#define MAX_LOADSTRING 100
#define _USE_MATH_DEFINES
#include <cmath>

// Глобальные переменные:
HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];

COLORREF axisColor = RGB(255, 0, 0);     
COLORREF graphColor = RGB(0, 0, 255);    
RECT clientRect;

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void DrawAxesAndGrid(HDC hdc, RECT rect, COLORREF color) {
    HPEN pen = CreatePen(PS_SOLID, 1, color);
    HGDIOBJ oldPen = SelectObject(hdc, pen);

    int w = rect.right - rect.left;
    int h = rect.bottom - rect.top;
    int midX = w / 2;
    int midY = h / 2;

    for (int x = 0; x <= w; x += 50)
        MoveToEx(hdc, x, 0, nullptr), LineTo(hdc, x, h);
    for (int y = 0; y <= h; y += 50)
        MoveToEx(hdc, 0, y, nullptr), LineTo(hdc, w, y);
   

    SelectObject(hdc, oldPen);
    DeleteObject(pen);
}

void DrawCosine(HDC hdc, RECT rect, COLORREF color) {
    HPEN pen = CreatePen(PS_SOLID, 2, color);
    HGDIOBJ oldPen = SelectObject(hdc, pen);

    int w = rect.right - rect.left;
    int h = rect.bottom - rect.top;
    int midX = w / 2;
    int midY = h / 2;

    double scaleX = 0.05;
    double scaleY = h / 4.0;

    MoveToEx(hdc, 0, midY - static_cast<int>(scaleY * cos((0 - midX) * scaleX)), nullptr);
    for (int x = 1; x < w; ++x) {
        double realX = (x - midX) * scaleX;
        double y = cos(realX);
        int drawY = midY - static_cast<int>(scaleY * y);
        LineTo(hdc, x, drawY);
    }

    SelectObject(hdc, oldPen);
    DeleteObject(pen);
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PRAC7, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance(hInstance, nCmdShow))
        return FALSE;

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PRAC7));

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) {
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
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PRAC7));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_PRAC7);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance;

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, 800, 600, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
        return FALSE;

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

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

    case WM_CHAR:
        std::swap(axisColor, graphColor);
        InvalidateRect(hWnd, nullptr, TRUE);
        break;

    case WM_SIZE:
        GetClientRect(hWnd, &clientRect);
        InvalidateRect(hWnd, nullptr, TRUE);
        break;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        DrawAxesAndGrid(hdc, clientRect, axisColor);
        DrawCosine(hdc, clientRect, graphColor);

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
