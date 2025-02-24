#pragma once
#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
class Queue {
private:
    static const int MAX = 10;
    T queue[MAX];
    int head, tail, length;

public:
    Queue() : head(0), tail(0), length(0) {}

    void put(T value) {
        if (length == MAX) {
            throw overflow_error("������! ������� �����������");
        }
        queue[tail] = value;
        tail = (tail + 1) % MAX;
        length++;

        cout << "������� " << value << " ������� � ������� " << " ������ � ��� " << getLength() << " ��������� " << "\n";

    }

    T get() {
        if (length == 0) {
            throw underflow_error("������! ������� �����");
        }
        T value = queue[head];
        head = (head + 1) % MAX;
        length--;

        cout << "������� " << value << " ������ �� ������� " << " ������ � ��� " << getLength() << " ��������� " << "\n";

        return value;

    }

    int getLength() const {
        return length;
    }
};

