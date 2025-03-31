#include <deque>
#include <iterator>
#include <algorithm>
#include <Windows.h>
#include "Employee.h"

int main() {
    SetConsoleOutputCP(1251);

    deque<Employee> deq1, deq2;


    ifstream file1("list.txt");
    istream_iterator<Employee> file_iter1(file1), end_iter;
    copy(file_iter1, end_iter, back_inserter(deq1));


    ifstream file2("list_1.txt");
    istream_iterator<Employee> file_iter2(file2);
    copy(file_iter2, end_iter, back_inserter(deq2));


    cout << "���������� ������ �� ����� list.txt\n";
    copy(deq1.begin(), deq1.end(), ostream_iterator<Employee>(cout, "\n"));


    cout << "���������� ������ �� ����� list_1.txt\n";
    copy(deq2.begin(), deq2.end(), ostream_iterator<Employee>(cout, "\n"));


    copy(deq2.begin(), deq2.end(), back_inserter(deq1));
    cout << "����������� ������ (���������� � ����� ������)\n";
    copy(deq1.begin(), deq1.end(), ostream_iterator<Employee>(cout, "\n"));


    deq1.erase(deq1.end() - deq2.size(), deq1.end());
    cout << "��������������� ������\n";
    copy(deq1.begin(), deq1.end(), ostream_iterator<Employee>(cout, "\n"));


    auto middle = deq1.begin() + deq1.size() / 2;

    copy(deq2.begin(), deq2.end(), inserter(deq1, middle));
    cout << "����������� ������ (���������� � �������� ������)\n";
    copy(deq1.begin(), deq1.end(), ostream_iterator<Employee>(cout, "\n"));

    return 0;
}