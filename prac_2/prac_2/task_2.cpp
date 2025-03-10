#include <iostream>
#include <algorithm>
#include <windows.h>
#include "distance.h"

using namespace std;

int main() {
    SetConsoleOutputCP(1251);

    Distance dist[] = {
        Distance(8, 25), 
        Distance(13, 6.5),  
        Distance(4, 48.5),   
        Distance(16, 130)  
    };

    int size = sizeof(dist) / sizeof(dist[0]);  

    cout << "Исходный массив:\n";
    for (int i = 0; i < size; i++) {
        cout << dist[i] << "\n";
    }
    cout << "\n";

    sort(dist, dist + size);
    cout << "Массив после сортировки по возрастанию:\n";
    for (int i = 0; i < size; i++) {
        cout << dist[i] << "\n";
    }
    cout << "\n";

    sort(dist, dist + size, greater<Distance>());
    cout << "Массив после сортировки по убыванию:\n";
    for (int i = 0; i < size; i++) {
        cout << dist[i] << "\n";
    }

    return 0;
}