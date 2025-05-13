// prac_7.cpp : ���������� ����� ����� ��� ����������.
//

#include "framework.h"
#include "prac_7.h"
#define MAX_LOADSTRING 100
#define _USE_MATH_DEFINES
#include <cmath>

// ���������� ����������:
HINSTANCE hInst;                                // ������� ���������
WCHAR szTitle[MAX_LOADSTRING];                  // ����� ������ ���������
WCHAR szWindowClass[MAX_LOADSTRING];            // ��� ������ �������� ����

// ��������� ���������� �������, ���������� � ���� ������ ����:
ATOM                MyRegisterClass(HINSTANCE hInstance);
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

    // TODO: ���������� ��� �����.

    // ������������� ���������� �����
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PRAC7, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // ��������� ������������� ����������:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PRAC7));

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



//
//  �������: MyRegisterClass()
//
//  ����: ������������ ����� ����.
//
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

//
//   �������: InitInstance(HINSTANCE, int)
//
//   ����: ��������� ������ ���������� � ������� ������� ����
//
//   �����������:
//
//        � ���� ������� ������ ���������� ����������� � ���������� ����������, � �����
//        ��������� � ��������� ������� ���� ���������.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // ��������� ������ ���������� � ���������� ����������

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

//
//  �������: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ����: ������������ ��������� � ������� ����.
//
//  WM_COMMAND  - ���������� ���� ����������
//  WM_PAINT    - ��������� �������� ����
//  WM_DESTROY  - ��������� ��������� � ������ � ���������
//
//
void draw(HDC hdc , POINT points[] ,HBRUSH hBrush ,long  sx, long sy, const TCHAR*text) {
    int size = sizeof(points) / sizeof(points[0]);

    SelectObject(hdc, hBrush);
    points[0] = { 0,0 };
    points[1] = { sx,0 };
    points[2] = { sx,sy };
    points[3] = { 0,sy };
    Polygon(hdc, points, size);

    SetTextColor(hdc, RGB(100, 200, 150));
    SetBkColor(hdc, RGB(20, 190, 50));

    for (int i = 0; i <= 3600; i += 180) {

        HFONT font = CreateFont(15, 10, i, 0, 700, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
            CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, (L"Arial"));;
        SelectObject(hdc, font);
        TextOut(hdc, sx / 2, sy / 2, text, 20);
    }
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    static long sx, sy;
    HDC hdc;
    POINT points[4];
    int size = sizeof(points) / sizeof(points[0]);
    
    const TCHAR* text = L"�����-�� �����";
    HBRUSH hBrush = CreateSolidBrush(RGB(255,255,255));

    switch (message)
    {
    case WM_SIZE:
        sx = LOWORD(lParam);
        sy = HIWORD(lParam);
        break;

    case WM_LBUTTONDOWN:
        hdc = GetDC(hWnd);
        draw(hdc, points, hBrush, sx, sy, text);
        break;
    case WM_RBUTTONDOWN:
        hdc = GetDC(hWnd);
        
        SelectObject(hdc, hBrush);

        points[0] = { 0,0 };
        points[1] = { sx,0 };
        points[2] = { sx,sy };
        points[3] = { 0,sy };

        Polygon(hdc, points, size);
        break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // ��������� ����� � ����:
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

        draw(hdc, points, hBrush, sx, sy, text);

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

// ���������� ��������� ��� ���� "� ���������".
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
