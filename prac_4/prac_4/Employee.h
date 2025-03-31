#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

class Employee {

    private:
        int id;
        string lastName;
        string name;
        double salary;
    
    public:
        friend istream& operator>>(istream& is, Employee& emp) {
            return is >> emp.id >> emp.lastName >> emp.name >> emp.salary;
        }

        friend ostream& operator<<(ostream& os, const Employee& emp) {
            return os << left << setw(5) << emp.id
                << setw(20) << emp.lastName
                << setw(15) << emp.name
                << setw(10) << fixed << setprecision(2) << emp.salary;
        }
};
