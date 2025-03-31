#include <iostream>
#include <vector>
#include <windows.h>

using namespace std;

int main() {
    SetConsoleOutputCP(1251);
    char charArray[] = "Аргентина манит негра";

    vector<char> text(charArray, charArray + sizeof(charArray) - 1); 

    cout << "Прямой порядок: ";
    for (vector<char>::iterator it = text.begin(); it != text.end(); ++it) {
        cout << *it;
    }
    cout << endl;

    cout << "Обратный порядок: ";
    for (vector<char>::reverse_iterator rIt = text.rbegin(); rIt != text.rend(); ++rIt) {
        cout << *rIt;
    }
    cout << endl;

    return 0;
}