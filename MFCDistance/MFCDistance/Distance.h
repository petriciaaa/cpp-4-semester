#pragma once
#include <cmath>

class Distance {
private:
    int meters;
    float centimeters;

    void normalize() {
        float totalCentimeters = meters * 100.0f + centimeters;

       
        meters = static_cast<int>(totalCentimeters / 100);
        centimeters = fmod(totalCentimeters, 100.0f);

        if (centimeters < 0) {
            meters -= 1;
            centimeters += 100.0f;
        }
    }

public:
    Distance() : meters(0), centimeters(0.0f) {}
    Distance(int m, float c) : meters(m), centimeters(c) {
        normalize();
    }

    Distance operator+(const Distance& d) const {
        return Distance(meters + d.meters, centimeters + d.centimeters);
    }

    Distance operator-(const Distance& d) const {
        return Distance(meters - d.meters, centimeters - d.centimeters);
    }

    Distance operator*(const Distance& d) const {
        float total1 = meters * 100.0f + centimeters;
        float total2 = d.meters * 100.0f + d.centimeters;
        float total = total1 * total2 / 100.0f;
        return Distance(0, total);
    }

    int get_met() const { return meters; }
    float get_cent() const { return centimeters; }
};
