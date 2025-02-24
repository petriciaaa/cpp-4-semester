#include <iostream>

using namespace std;

class Distance {
private:
    int meters;
    double centimeters;

public:
    Distance() : meters(0), centimeters(0) {}
    Distance(int m, double cm) : meters(m), centimeters(cm) {}

    friend ostream& operator<< (ostream& os, const Distance& d) {
        os << d.meters << " метра "<< d.centimeters << " сантиметров ";
        return os;
    }

    friend istream& operator>> (istream& is, Distance& d) {
        is >> d.meters;
        is >> d.centimeters;
        return is;
    }

};
