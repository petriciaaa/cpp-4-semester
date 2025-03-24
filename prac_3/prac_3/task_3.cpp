#include <iostream>
#include <stack>
#include <windows.h>

using namespace std;

int main() {

    SetConsoleOutputCP(1251);

    stack<COORD> coordStack;

    COORD point[4] = {
        {1, 2},
        {3, 4},
        {5, 6},
        {7, 8}
    };

    cout << "����� � ������������ (" << point[0].X << ", " << point[0].Y << ") �������� � ����" << endl;
    coordStack.push(point[0]);
    cout << "����� � ������������ (" << point[1].X << ", " << point[1].Y << ") �������� � ����" << endl;
    coordStack.push(point[1]);
    cout << "����� � ������������ (" << point[2].X << ", " << point[2].Y << ") �������� � ����" << endl;
    coordStack.push(point[2]);
    cout << "����� � ������������ (" << point[3].X << ", " << point[3].Y << ") �������� � ����" << endl;
    coordStack.push(point[3]);

    cout << "� ���������� ��������� " << coordStack.size() << " ��������(��)" << endl;

    COORD topPoint = coordStack.top();
    cout << "����� � ������������ (" << topPoint.X << ", " << topPoint.Y << ") ��������� �� �����" << endl;
    coordStack.pop();

    topPoint = coordStack.top();
    cout << "����� � ������������ (" << topPoint.X << ", " << topPoint.Y << ") ��������� �� �����" << endl;
    coordStack.pop();

    cout << "� ���������� ��������� " << coordStack.size() << " ��������(��)" << endl;

    cout << "����� � ������������ (" << point[0].X << ", " << point[0].Y << ") �������� � ����" << endl;
    coordStack.push(point[0]);
    cout << "����� � ������������ (" << point[1].X << ", " << point[1].Y << ") �������� � ����" << endl;
    coordStack.push(point[1]);
    cout << "����� � ������������ (" << point[2].X << ", " << point[2].Y << ") �������� � ����" << endl;
    coordStack.push(point[2]);
    cout << "����� � ������������ (" << point[3].X << ", " << point[3].Y << ") �������� � ����" << endl;
    coordStack.push(point[3]);

    cout << "� ���������� ��������� " << coordStack.size() << " ��������(��)" << endl;

    while (coordStack.size() > 0) {
        topPoint = coordStack.top();
        cout << "����� � ������������ (" << topPoint.X << ", " << topPoint.Y << ") ��������� �� �����" << endl;
        coordStack.pop();
    }

    cout << "� ���������� ��������� " << coordStack.size() << " ��������(��)" << endl;

    return 0;
}