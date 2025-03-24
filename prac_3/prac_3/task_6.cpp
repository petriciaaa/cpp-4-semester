#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include <windows.h>

using namespace std;

using BankRecord = pair<int, string>;  

struct Compare {
    bool operator()(const BankRecord& a, const BankRecord& b) {
        return a.first < b.first;  
    }
};

void writeRecords(priority_queue<BankRecord, vector<BankRecord>, Compare>& pq, const char* fileName) {
    ofstream out(fileName);
    if (!out.is_open()) {
        cout << "Ошибка открытия файла для записи!" << endl;
        return;
    }

    priority_queue<BankRecord, vector<BankRecord>, Compare> temp = pq;
    int count = 0;

    while (!temp.empty()) {
        out << temp.top().first << temp.top().second << endl;
        temp.pop();
        count++;
    }

    out.close();
    cout << "Записано " << count << " записей в файл " << fileName << endl;
}

int main() {
    SetConsoleOutputCP(1251);

    ifstream in("NAMES.TXT");
    if (!in.is_open()) {
        cout << "Ошибка открытия файла NAMES.TXT!" << endl;
        return 1;
    }

    priority_queue<BankRecord, vector<BankRecord>, Compare> bankQueue;
    char ch;
    string buffer;

    while (in.get(ch)) {
        BankRecord record;

        buffer.clear();
        while (ch != ';' && !in.eof()) {
            buffer += ch;
            in.get(ch);
        }
        record.first = atoi(buffer.c_str());  

        buffer.clear();
        while (ch != '\n' && !in.eof()) {
            buffer += ch;
            in.get(ch);
        }
        record.second = buffer;

        bankQueue.push(record);
    }

    in.close();
    cout << "Считано " << bankQueue.size() << " записей из файла NAMES.TXT" << endl;

    cout << "\nОтсортированные записи (по убыванию номера):\n";
    priority_queue<BankRecord, vector<BankRecord>, Compare> displayQueue = bankQueue;
    while (!displayQueue.empty()) {
        cout << displayQueue.top().first << displayQueue.top().second << endl;
        displayQueue.pop();
    }

    writeRecords(bankQueue, "NAMES_sorted.TXT");

    return 0;
}