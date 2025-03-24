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

    cout << "Точка с координатами (" << point[0].X << ", " << point[0].Y << ") помещена в стек" << endl;
    coordStack.push(point[0]);
    cout << "Точка с координатами (" << point[1].X << ", " << point[1].Y << ") помещена в стек" << endl;
    coordStack.push(point[1]);
    cout << "Точка с координатами (" << point[2].X << ", " << point[2].Y << ") помещена в стек" << endl;
    coordStack.push(point[2]);
    cout << "Точка с координатами (" << point[3].X << ", " << point[3].Y << ") помещена в стек" << endl;
    coordStack.push(point[3]);

    cout << "В контейнере находится " << coordStack.size() << " элемента(ов)" << endl;

    COORD topPoint = coordStack.top();
    cout << "Точка с координатами (" << topPoint.X << ", " << topPoint.Y << ") извлечена из стека" << endl;
    coordStack.pop();

    topPoint = coordStack.top();
    cout << "Точка с координатами (" << topPoint.X << ", " << topPoint.Y << ") извлечена из стека" << endl;
    coordStack.pop();

    cout << "В контейнере находится " << coordStack.size() << " элемента(ов)" << endl;

    cout << "Точка с координатами (" << point[0].X << ", " << point[0].Y << ") помещена в стек" << endl;
    coordStack.push(point[0]);
    cout << "Точка с координатами (" << point[1].X << ", " << point[1].Y << ") помещена в стек" << endl;
    coordStack.push(point[1]);
    cout << "Точка с координатами (" << point[2].X << ", " << point[2].Y << ") помещена в стек" << endl;
    coordStack.push(point[2]);
    cout << "Точка с координатами (" << point[3].X << ", " << point[3].Y << ") помещена в стек" << endl;
    coordStack.push(point[3]);

    cout << "В контейнере находится " << coordStack.size() << " элемента(ов)" << endl;

    while (coordStack.size() > 0) {
        topPoint = coordStack.top();
        cout << "Точка с координатами (" << topPoint.X << ", " << topPoint.Y << ") извлечена из стека" << endl;
        coordStack.pop();
    }

    cout << "В контейнере находится " << coordStack.size() << " элемента(ов)" << endl;

    return 0;
}