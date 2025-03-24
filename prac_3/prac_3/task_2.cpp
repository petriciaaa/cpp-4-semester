#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <windows.h>

using namespace std;

struct names {
    int number;    
    string nameB; 
};

bool compNumLess(const names& a, const names& b) {
    return a.number < b.number;
}

void writeNames(const vector<names>& vName, const char* fileName) {
    ofstream out(fileName);
    if (!out.is_open()) {
        cout << "Ошибка открытия файла для записи!" << endl;
        return;
    }

    for (size_t i = 0; i < vName.size(); i++) {
        out << vName[i].number << vName[i].nameB << endl;
    }

    out.close();
    cout << "Записано " << vName.size() << " записей в файл " << fileName << endl;
}

int main() {

    SetConsoleOutputCP(1251);

    ifstream in("NAMES.TXT");
    if (!in.is_open()) {
        cout << "Ошибка открытия файла NAMES.TXT!" << endl;
        return 1;
    }

    vector<names> vName;
    char ch;
    string buffer;

    while (in.get(ch)) { 
        names record;

        buffer.clear();
        while (ch != ';' && !in.eof()) {
            buffer += ch;
            in.get(ch);
        }
        record.number = atoi(buffer.c_str()); 

        buffer.clear();
        while (ch != '\n' && !in.eof()) {
            buffer += ch;
            in.get(ch);
        }
        record.nameB = buffer;

        vName.push_back(record);
    }

    in.close();
    cout << "Считано " << vName.size() << " записей из файла NAMES.TXT" << endl;

    sort(vName.begin(), vName.end(), compNumLess);
    cout << "Сортировка..." << endl;

    writeNames(vName, "NAMES_sort.TXT");

    return 0;
}