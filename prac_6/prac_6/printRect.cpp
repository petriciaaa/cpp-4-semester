#include "printRect.h"
void printRect(const Rect rect) {

    HWND hWindow = GetConsoleWindow();
    HDC hDeviceContext = GetDC(hWindow);

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
    SelectObject(hDeviceContext, hBrush);
    Rectangle(
        hDeviceContext,
        rect.leftCorner.X,
        rect.leftCorner.Y,
        rect.rightCorner.X,
        rect.rightCorner.Y);

    DeleteObject(hBrush);

    HPEN hPen = CreatePen(PS_SOLID, 0, color);
    SelectObject(hDeviceContext, hPen);
    Rectangle(
        hDeviceContext,
        rect.leftCorner.X,
        rect.leftCorner.Y,
        rect.rightCorner.X,
        rect.rightCorner.Y);

    DeleteObject(hPen);
    ReleaseDC(hWindow, hDeviceContext);


}