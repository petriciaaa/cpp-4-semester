#include <iostream>
#include <windows.h>
#include <algorithm>
#include <iomanip>

using namespace std;

int main() {
    SetConsoleOutputCP(1251);

    const int MAX_SIZE = 1000; 
    float arr[MAX_SIZE];      
    int count = 0;            
    char choice;

    do {
        if (count >= MAX_SIZE) {
            cout << "Достигнут максимальный размер массива!\n";
            break;
        }

        float value;
        cout << "Введите число с плавающей точкой: ";
        cin >> value;
        arr[count] = value;
        count++;

        cout << "Продолжить ввод? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    cout << "\nИсходный массив:\n";
    for (int i = 0; i < count; i++) {
        cout << setw(10) << arr[i];
    }
    cout << "\n";

    sort(arr, arr + count);
    cout << "\nМассив после сортировки по возрастанию:\n";
    for (int i = 0; i < count; i++) {
        cout << setw(10) << arr[i];
    }
    cout << "\n";

    sort(arr, arr + count, greater<float>());
    cout << "\nМассив после сортировки по убыванию:\n";
    for (int i = 0; i < count; i++) {
        cout << setw(10) << arr[i];
    }
    cout << "\n";

    return 0;
}