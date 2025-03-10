#include <iostream>
#include <algorithm>
#include <windows.h>
#include <string>

using namespace std;

void myPrint(const string& word) {
    cout << "�����: " << word << "\n";
}

void myCount(const string& word) {
    cout << "� ����� " << word  << " "  << word.length() << " ����" << "\n";
}

int main() {
    SetConsoleOutputCP(1251);

    string words[] = {
        "������������",
        "�������",
        "���������",
        "1",
        "22"
    };

    int size = sizeof(words) / sizeof(words[0]);

    cout << "\n";
    for_each(words, words + size, myPrint);

    cout << "\n";
    for_each(words, words + size, myCount);

    return 0;
}