// prac_6.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "string"
#include <time.h>
#include "prac_6.h"

#define MAX_LOADSTRING 100

using namespace std;

struct Rect {
    COORD leftCorner;
    COORD rightCorner;
    char color;
};

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
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

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PRAC6, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PRAC6));

    MSG msg;

    // Цикл основного сообщения:
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
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
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
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PRAC6));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_PRAC6);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

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
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//

void drawCircle(HDC hDeviceContext, const COORD CENTER, double radius, COLORREF color, bool stroke = true) {


    HBRUSH hBrush = CreateSolidBrush(color);
    HPEN hPen = (HPEN)GetStockObject(NULL_PEN);

    if (!stroke)
    {
        HBRUSH hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
        SelectObject(hDeviceContext, hPen);
    }

    SelectObject(hDeviceContext, hBrush);

    Ellipse(hDeviceContext, CENTER.X - radius, CENTER.Y - radius, CENTER.X + radius, CENTER.Y + radius);
    DeleteObject(hPen);
    DeleteObject(hBrush);

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Разобрать выбор в меню:
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

        const int WindowHeight = 600 - 15, WindowWidth = 1440 - 15;
        //const int WindowHeight = 1440 - 15, WindowWidth = 600 - 15;

        srand(time(NULL));


        int directionX = 1;
        int directionY = 1;
        int pounceCounter = 0;
        const int radius = 15;


        COLORREF color = RGB(rand() % 255, rand() % 255, rand() % 255);
        COORD start = { rand() % (WindowWidth - 1) ,rand() % (WindowHeight - 1) };

        COORD prevStart = start;
        int speed = 120;


        while (true)
        {

            drawCircle(hdc, prevStart, 15, RGB(230, 230, 250), false);
            drawCircle(hdc, start, 15, color);

            int x = start.X;
            int y = start.Y;
            x += directionX * radius;
            y += directionY * radius;

            if (x == radius / 2 && y == radius / 2 || x == radius / 2 && y == WindowHeight - radius / 2 - 1 ||
                x == WindowWidth - radius / 2 - 1 && y == radius / 2 - 1 || x == WindowWidth - radius / 2 - 1 && y == WindowHeight - radius / 2 - 1)
            {

                directionX = -directionX;
                directionY = -directionY;
                speed -= 10;
                color = RGB(rand() % 255, rand() % 255, rand() % 255, );

            }
            else if (x <= radius || x >= WindowWidth - radius / 2)
            {

                directionX = -directionX;
                speed -= 10;
                color = RGB(rand() % 255, rand() % 255, rand() % 255, );

            }
            else if (y <= radius || y >= WindowHeight - radius / 2) {

                directionY = -directionY;
                speed -= 10;
                color = RGB(rand() % 255, rand() % 255, rand() % 255, );

            }
            prevStart = start;

            start = { short(x),short(y) };
            pounceCounter++;

            Sleep(speed >= 0 ? speed : 1);



        }


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

// Обработчик сообщений для окна "О программе".
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
