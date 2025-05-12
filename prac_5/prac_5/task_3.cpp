#include <iostream>
#include <map>
#include <string>
#include <windows.h>
#include <vector>

using namespace std;


class Person {
public:
    string lastName;
    string name;

    Person(string lastName, string name)
        : lastName(lastName), name(name) {
    }

    void display() const {
        cout << lastName << "   " << name;
    }
};


struct CompPers {
    bool operator()(const Person& person1, const Person& person2) const {
        return person1.lastName < person2.lastName;
    }
};

Person getPersonData() {
    string lastName, name;
    cout << "Enter last name: ";
    cin >> lastName;
    cout << "Enter name: ";
    cin >> name;
    return Person(lastName, name);
}

vector<pair<Person, string>> findMatchingPersons(const multimap<Person, string, CompPers>& phoneBook, const Person& personToFind) {
    vector<pair<Person, string>> matches;
    for (const auto& entry : phoneBook) {
        if (entry.first.lastName == personToFind.lastName && entry.first.name == personToFind.name) {
            matches.push_back(entry);
        }
    }
    return matches;
}

void removeSpecificPerson(multimap<Person, string, CompPers>& phoneBook, const Person& personToRemove, const string& phoneNumber) {
    for (auto it = phoneBook.begin(); it != phoneBook.end();) {
        if (it->first.lastName == personToRemove.lastName &&
            it->first.name == personToRemove.name &&
            it->second == phoneNumber) {
            it = phoneBook.erase(it);
            break; 
        }
        else {
            ++it;
        }
    }
}

void updatePhoneNumber(multimap<Person, string, CompPers>& phoneBook, const Person& person, const string& oldPhoneNumber) {
    cout << "Current entry: ";
    person.display();
    cout << "   " << oldPhoneNumber << endl;
    string newPhoneNumber;
    cout << "Enter new phone number: ";
    cin.ignore(); 
    getline(cin, newPhoneNumber); 
    phoneBook.insert(make_pair(person, newPhoneNumber));
}

void displayPhoneBook(const multimap<Person, string, CompPers>& phoneBook) {
    cout << "Phone book contents: " << endl;
    for (const auto& entry : phoneBook) {
        entry.first.display();
        cout << "   " << entry.second << endl;
    }
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    multimap<Person, string, CompPers> phoneBook;

    phoneBook.insert(make_pair(Person("Иванова", "Екатерина"), "Tel.: 355-51-50"));
    phoneBook.insert(make_pair(Person("Кузнецова", "Татьяна"), "Tel.: 504-64-73"));
    phoneBook.insert(make_pair(Person("Петров", "Виктор"), "Tel.: 444-73-25"));
    phoneBook.insert(make_pair(Person("Петров", "Игорь"), "Tel.: 322-75-63"));
    phoneBook.insert(make_pair(Person("Петров", "Игорь"), "Tel.: 352-48-14"));

    cout << "Initial number of entries: " << phoneBook.size() << endl;
    displayPhoneBook(phoneBook);

    cout << "\nEnter the person to update: " << endl;
    Person personToUpdate = getPersonData();

    auto matches = findMatchingPersons(phoneBook, personToUpdate);

    if (matches.empty()) {
        cout << "No entries found for: " << personToUpdate.lastName << " " << personToUpdate.name << endl;
    }
    else {
        for (const auto& match : matches) {
            removeSpecificPerson(phoneBook, match.first, match.second);
            updatePhoneNumber(phoneBook, match.first, match.second);
        }
    }

    cout << "\nUpdated phone book: " << endl;
    cout << "Number of entries after update: " << phoneBook.size() << endl;
    displayPhoneBook(phoneBook);

    return 0;
}