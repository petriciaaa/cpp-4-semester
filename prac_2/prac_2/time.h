#pragma once
#include <iostream>
#include <iomanip>
using namespace std;

class Time {
private:
    int hours;
    int minutes;
    int seconds;

public:
    Time(int h = 0, int m = 0, int s = 0) : hours(h), minutes(m), seconds(s) {
        normalize();
    }

    void normalize() {
        if (seconds >= 60) {
            minutes += seconds / 60;
            seconds %= 60;
        }
        if (minutes >= 60) {
            hours += minutes / 60;
            minutes %= 60;
        }
    }

    friend ostream& operator<<(ostream& os, const Time& t) {
        os << setw(2) << setfill('0') << t.hours << ":"
            << setw(2) << setfill('0') << t.minutes << ":"
            << setw(2) << setfill('0') << t.seconds;
        return os;
    }
};