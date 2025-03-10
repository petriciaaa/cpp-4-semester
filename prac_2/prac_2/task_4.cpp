#include <iostream>
#include <algorithm>
#include <windows.h>
#include <iomanip>
#include "time.h"

using namespace std;

Time secToTime(int seconds) {
    int hours = seconds / 3600;      
    int minutes = (seconds % 3600) / 60; 
    int secondsLeft = seconds % 60;   
    return Time(hours, minutes, secondsLeft);
}

int main() {
    SetConsoleOutputCP(1251);

    int secondsArray[] = { 59, 359, 1000, 3601};
    int size = sizeof(secondsArray) / sizeof(secondsArray[0]);

    Time timeArray[5];  

    transform(secondsArray, secondsArray + size, timeArray, secToTime);

    cout << "Исходный массив:\n";
    for (int i = 0; i < size; i++) {
        cout << secondsArray[i] << " ";
    }
    cout << "\n\n";

    cout << "Преобразованный массив:\n";
    for (int i = 0; i < size; i++) {
        cout << timeArray[i] << "\n";
    }

    return 0;
}