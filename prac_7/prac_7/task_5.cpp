#include <windows.h>
#include "resource.h"

HBITMAP hBitmap = nullptr;
int bmpWidth = 0, bmpHeight = 0;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void AdjustWindowToImage(HWND hWnd) {
    RECT rect = { 0, 0, bmpWidth, bmpHeight };
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, TRUE);
    SetWindowPos(hWnd, nullptr, 100, 100, rect.right - rect.left, rect.bottom - rect.top, SWP_NOZORDER);
}

void LoadAndShowBitmap(HWND hWnd, const wchar_t* path) {
    if (hBitmap) DeleteObject(hBitmap);
    hBitmap = (HBITMAP)LoadImageW(nullptr, path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    if (hBitmap) {
        BITMAP bmp;
        GetObject(hBitmap, sizeof(bmp), &bmp);
        bmpWidth = bmp.bmWidth;
        bmpHeight = bmp.bmHeight;
        AdjustWindowToImage(hWnd);
        InvalidateRect(hWnd, nullptr, TRUE);
    }
}

void ApplyInvert(HWND hWnd) {
    if (!hBitmap) return;
    HDC hdc = GetDC(hWnd);
    HDC memDC = CreateCompatibleDC(hdc);
    SelectObject(memDC, hBitmap);

    for (int y = 0; y < bmpHeight; ++y) {
        for (int x = 0; x < bmpWidth; ++x) {
            COLORREF c = GetPixel(memDC, x, y);
            SetPixel(memDC, x, y, RGB(255 - GetRValue(c), 255 - GetGValue(c), 255 - GetBValue(c)));
        }
    }

    DeleteDC(memDC);
    ReleaseDC(hWnd, hdc);
    InvalidateRect(hWnd, nullptr, TRUE);
}

void ApplyGrayscale(HWND hWnd) {
    if (!hBitmap) return;
    HDC hdc = GetDC(hWnd);
    HDC memDC = CreateCompatibleDC(hdc);
    SelectObject(memDC, hBitmap);

    for (int y = 0; y < bmpHeight; ++y) {
        for (int x = 0; x < bmpWidth; ++x) {
            COLORREF c = GetPixel(memDC, x, y);
            BYTE gray = BYTE(0.3 * GetRValue(c) + 0.59 * GetGValue(c) + 0.11 * GetBValue(c));
            SetPixel(memDC, x, y, RGB(gray, gray, gray));
        }
    }

    DeleteDC(memDC);
    ReleaseDC(hWnd, hdc);
    InvalidateRect(hWnd, nullptr, TRUE);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int nCmdShow) {
    const wchar_t CLASS_NAME[] = L"ImageWindowClass";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClass(&wc);

    HWND hWnd = CreateWindowEx(0, CLASS_NAME, L"Image Viewer", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, nullptr, LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU)), hInstance, nullptr);

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    if (hBitmap) DeleteObject(hBitmap);

    return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case IDM_LOAD: {
            OPENFILENAME ofn = {};
            wchar_t szFile[MAX_PATH] = {};
            ofn.lStructSize = sizeof(ofn);
            ofn.hwndOwner = hWnd;
            ofn.lpstrFilter = L"Bitmap Files\0*.bmp\0";
            ofn.lpstrFile = szFile;
            ofn.nMaxFile = MAX_PATH;
            ofn.Flags = OFN_FILEMUSTEXIST;

            if (GetOpenFileName(&ofn)) {
                LoadAndShowBitmap(hWnd, szFile);
            }
            break;
        }
        case IDM_CLEAR:
            if (hBitmap) {
                DeleteObject(hBitmap);
                hBitmap = nullptr;
                InvalidateRect(hWnd, nullptr, TRUE);
            }
            break;
        case IDM_INVERT:
            ApplyInvert(hWnd);
            break;
        case IDM_GRAYSCALE:
            ApplyGrayscale(hWnd);
            break;
        }
        break;

    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        if (hBitmap) {
            HDC memDC = CreateCompatibleDC(hdc);
            SelectObject(memDC, hBitmap);
            BitBlt(hdc, 0, 0, bmpWidth, bmpHeight, memDC, 0, 0, SRCCOPY);
            DeleteDC(memDC);
        }
        EndPaint(hWnd, &ps);
        break;
    }

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}
