#pragma once
#include <iostream>
using namespace std;

class Distance {
private:
    float meters;
    float centimeters;

public:
    Distance(float m = 0, float cm = 0) : meters(m), centimeters(cm) {
        normalize();
    }

    void normalize() {
        if (centimeters >= 100) {
            meters += centimeters / 100;
            centimeters = fmod(centimeters, 100);
        }
    }

    friend ostream& operator<<(ostream& os, const Distance& d) {
        os << d.meters << " м " << d.centimeters << " см";
        return os;
    }

    friend istream& operator>>(istream& is, Distance& d) {
        is >> d.meters >> d.centimeters;
        d.normalize();
        return is;
    }

    bool operator<(const Distance& other) const {
        if (meters != other.meters) {
            return meters < other.meters;
        }
        return centimeters < other.centimeters;
    }

    bool operator>(const Distance& other) const {
        if (meters != other.meters) {
            return meters > other.meters;
        }
        return centimeters > other.centimeters;
    }
};