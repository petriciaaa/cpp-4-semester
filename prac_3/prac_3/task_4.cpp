#include <iostream>
#include <fstream>
#include <deque>
#include <iomanip>
#include <windows.h>

using namespace std;

struct person {
    int id;
    string name;
    float salary;
};

void readF(deque<person>& deq, const char* fileName) {
    ifstream in(fileName);
    if (!in.is_open()) {
        cout << "������ �������� ����� " << fileName << "!" << endl;
        return;
    }

    cout << "���������� ����� " << fileName << ":\n";
    cout << in.rdbuf() << endl << endl;
    in.close();

    in.open(fileName);
    if (!in.is_open()) {
        cout << "������ ���������� �������� ����� " << fileName << "!" << endl;
        return;
    }

    int id;
    string firstName, lastName;
    float salary;
    while (in >> id >> firstName >> lastName >> salary) {
        person p;
        p.id = id;
        p.name = firstName + " " + lastName; 
        p.salary = salary;
        deq.push_back(p);
    }

    in.close();
    cout << "������� " << deq.size() << " ������� �� ����� " << fileName << endl;
}

void addDeq(deque<person>& deqDest, const deque<person>& deqSrc) {
    for (const auto& p : deqSrc) {
        deqDest.push_back(p);
    }
}

void showDeq(const deque<person>& deq) {
    cout << "ID\t�������\t\t��������" << endl;
    for (const auto& p : deq) {
        cout << p.id << "\t" << left << setw(20) << p.name << "\t" << fixed << setprecision(2) << p.salary << endl;
    }
    cout << "�������� ������: " << deq.size() << " �������" << endl;
}

void writeF(const deque<person>& deq, const char* fileName) {
    ofstream out(fileName);
    if (!out.is_open()) {
        cout << "������ �������� ����� " << fileName << " ��� ������!" << endl;
        return;
    }

    for (const auto& p : deq) {
        out << p.id << " " << p.name << " " << p.salary << endl;
    }

    out.close();
    cout << "�������� " << deq.size() << " ������� � ���� " << fileName << endl;
}

int main() {

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    deque<person> deq;
    deque<person> deq1;

    readF(deq, "list.txt");
    readF(deq1, "list_1.txt");

    cout << "������ ����������� �� list.txt:" << endl;
    showDeq(deq);
    cout << endl;

    cout << "������ ����������� �� list_1.txt:" << endl;
    showDeq(deq1);
    cout << endl;

    addDeq(deq, deq1);

    cout << "���������� ������:" << endl;
    showDeq(deq);
    cout << endl;

    writeF(deq, "list_res.txt");

    return 0;
}