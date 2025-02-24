#pragma once
#include <iostream>

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
            cout << "ќчередь переполнена \n";

            return;
        }
        queue[tail] = value;
        tail = (tail + 1) % MAX;
        length++;

        cout << "Ёлемент " << value << " помещен в очередь " << " сейчас в ней " << getLength() << " элементов " << "\n";

    }

    T get() {
        if (length == 0) {
            cout << "ќчередь пуста \n";
            return T(); 
        }
        T value = queue[head];
        head = (head + 1) % MAX;
        length--;

        cout << "Ёлемент " << value << " удален из очереди " << " сейчас в ней " << getLength() << " элементов " << "\n";

        return value;

    }

    int getLength() const {
        return length;
    }
};

