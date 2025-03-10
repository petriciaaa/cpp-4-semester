#include <iostream>
#include <algorithm>
#include <windows.h>

using namespace std;



bool increasing(COORD a, COORD b) {
    if (a.X != b.X) {
        return a.X < b.X;
    }
    return a.Y < b.Y;
}

bool decreasing(COORD a, COORD b) {
    if (a.X != b.X) {
        return a.X > b.X;
    }
    return a.Y > b.Y;
}

int main() {
    SetConsoleOutputCP(1251);

    COORD points[] = {
        {10, 15},
        {1, 2},
        {1, 1},
        {8, 4},
        {8, 6},
        {0, 6},
        {5, 9},
    };

    int size = sizeof(points) / sizeof(points[0]); 

    cout << "Исходный массив:\n";
    for (int i = 0; i < size; i++) {
        cout << "(" << points[i].X << ", " << points[i].Y << ") ";
    }
    cout << "\n\n";

    sort(points, points + size, increasing);
    cout << "Массив после сортировки по возрастанию:\n";
    for (int i = 0; i < size; i++) {
        cout << "(" << points[i].X << ", " << points[i].Y << ") ";
    }
    cout << "\n\n";

    sort(points, points + size, decreasing);
    cout << "Массив после сортировки по убыванию:\n";
    for (int i = 0; i < size; i++) {
        cout << "(" << points[i].X << ", " << points[i].Y << ") ";
    }
    cout << "\n";

    return 0;
}