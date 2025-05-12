// prac_6.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "string"
#include "prac_6.h"

#define MAX_LOADSTRING 100
#define ID_BUTTON_1 200
#define ID_BUTTON_2 201
#define ID_BUTTON_3 202


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
    HWND hWnd_button;

    if (!hWnd)
    {
        return FALSE;
    }
    hWnd_button = CreateWindow(L"Button", L"Рисиуем прямоугольники", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 150, 600, 200, 100, hWnd, (HMENU)ID_BUTTON_1, hInstance, NULL);
    hWnd_button = CreateWindow(L"Button", L"Рисиуем круги", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 500, 600, 200, 100, hWnd, (HMENU)ID_BUTTON_2, hInstance, NULL);
    hWnd_button = CreateWindow(L"Button", L"Чистим экран", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 850, 600, 200, 100, hWnd, (HMENU)ID_BUTTON_3, hInstance, NULL);
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
void drawCircle(HDC hDeviceContext, const COORD CENTER, double radius, COLORREF color) {

    HBRUSH hBrush = CreateSolidBrush(color);
    SelectObject(hDeviceContext, hBrush);
    Ellipse(hDeviceContext, CENTER.X - radius, CENTER.Y - radius, CENTER.X + radius, CENTER.Y + radius);
    DeleteObject(hBrush);

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  /*  int mMid, wmEvent;
    PAINTSTRUCT ps;*/
   static bool drawRectangles = false;
   static bool drawCircles = false;

    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        int wmEvent = HIWORD(wParam);
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;   
        case ID_BUTTON_1:
            drawRectangles = true;  
            drawCircles = false;  
            InvalidateRect(hWnd, NULL, TRUE);  
            break; 
        case ID_BUTTON_2:
            drawRectangles = false;  
            drawCircles = true;
            InvalidateRect(hWnd, NULL, TRUE);  
            break; 
        case ID_BUTTON_3:
            drawRectangles = false;  
            drawCircles = false;
            InvalidateRect(hWnd, NULL, TRUE);  
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

        if (drawRectangles)
        {
            const short WINDOW_WIDTH = 1100;
            const short WINDOW_HEIGH = 600;

            const Rect arr[] = {
               {{0,0},{WINDOW_WIDTH / 2,WINDOW_HEIGH / 2},'R'},
               {{WINDOW_WIDTH / 2,0},{WINDOW_WIDTH ,WINDOW_HEIGH / 2},'G'},
               {{0,WINDOW_HEIGH / 2},{WINDOW_WIDTH / 2,WINDOW_HEIGH },'B'},
               {{WINDOW_WIDTH / 2,WINDOW_HEIGH / 2},{WINDOW_WIDTH ,WINDOW_HEIGH },'J'}
            };

            for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
            {
                const Rect rect = (arr[i]);

                COLORREF color;
                switch (rect.color) {
                case 'R':
                    color = RGB(255, 0, 0);
                    break;

                case 'G':
                    color = RGB(0, 255, 0);
                    break;

                case 'B':
                    color = RGB(0, 0, 255);
                    break;

                default:
                    color = RGB(0, 0, 0);
                    break;

                }

                HBRUSH hBrush = CreateSolidBrush(color);
                SelectObject(hdc, hBrush);
                Rectangle(
                    hdc,
                    rect.leftCorner.X,
                    rect.leftCorner.Y,
                    rect.rightCorner.X,
                    rect.rightCorner.Y);

                DeleteObject(hBrush);

                HPEN hPen = CreatePen(PS_SOLID, 0, color);
                SelectObject(hdc, hPen);
                Rectangle(
                    hdc,
                    rect.leftCorner.X,
                    rect.leftCorner.Y,
                    rect.rightCorner.X,
                    rect.rightCorner.Y);

                DeleteObject(hPen);

            }

        }

        if (drawCircles)
        {
            const int windowHeight = 1000;

            const COLORREF COLOR_BLACK = RGB(0, 0, 0);
            const COLORREF  COLOR_WHITE = RGB(255, 255, 255);
            const int CIRCLES_COUNTER = 10;
            const COORD CENTER = { 700,300 };
            const int RADIUS_SCALE = 25;

            for (int i = CIRCLES_COUNTER; i > 0; i--)
            {
                drawCircle(hdc, CENTER, RADIUS_SCALE * i, i % 2 == 0 ? COLOR_WHITE : COLOR_BLACK);

            }

            for (int i = CIRCLES_COUNTER; i >= 0; i--)
            {

                std::string text = (CIRCLES_COUNTER - i) % 2 == 0 && CIRCLES_COUNTER != i ? std::to_string(CIRCLES_COUNTER - i) : "";
                SetBkColor(hdc, COLOR_BLACK);
                SetTextColor(hdc, COLOR_WHITE);

                const char* ctext = text.c_str();
                if (!i)
                {
                    TextOutA(hdc, CENTER.X - 8 + (RADIUS_SCALE * i), CENTER.Y - 8, ctext, strlen(ctext));

                }
                else {
                    // 8 px - one char width i height ( maybe thats an false, stack thx)
                    const int charSize = 8;
                    TextOutA(hdc, CENTER.X + charSize + (RADIUS_SCALE * i), CENTER.Y - 8, ctext, strlen(ctext));
                    TextOutA(hdc, CENTER.X - charSize * 2 - (RADIUS_SCALE * i), CENTER.Y - 8, ctext, strlen(ctext));
                }

            }

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
