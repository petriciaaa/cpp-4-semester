#include <iostream>
#include <set>
#include <string>
#include <windows.h>

using namespace std;

class Person {
public:
    string lastName;
    string name;
    string phoneNumber;

    Person(string lastName, string name, string phoneNumber)
        : lastName(lastName), name(name), phoneNumber(phoneNumber) {
    }

    void display() const {
        cout << lastName << "   " << name << "   " << phoneNumber << endl;
    }
};

struct CompPers {
    bool operator()(const Person* person1, const Person* person2) const {
        return person1->lastName < person2->lastName;
    }
};

int main() {
    SetConsoleOutputCP(1251);

    multiset<Person*, CompPers> personSet;

    const int numPersons = 6;
    Person* personArray[numPersons];

    personArray[0] = new Person("Петров", "Виктор", "Tel.: 444-73-25");
    personArray[1] = new Person("Иванова", "Татьяна", "Tel.: 594-64-73");
    personArray[2] = new Person("Кузнецов", "Илья", "Tel.: 306-74-82");
    personArray[3] = new Person("Петров", "Игорь", "Tel.: 352-48-14");
    personArray[4] = new Person("Иванова", "Екатерина", "Tel.: 355-51-50");
    personArray[5] = new Person("Петров", "Игорь", "Tel.: 322-75-63");

    multiset<Person*, CompPers>::iterator it = personSet.begin();
    for (int i = 0; i < numPersons; i++) {
        it = personSet.insert(it, personArray[i]);
    }

    cout << "Sorted list of persons:" << endl;
    for (multiset<Person*, CompPers>::iterator it = personSet.begin(); it != personSet.end(); ++it) {
        (*it)->display();
    }

    for (int i = 0; i < numPersons; i++) {
        delete personArray[i];
    }

    return 0;
}