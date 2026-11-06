#include <iostream>

class Time {
    int h, m;

public:
    Time(int hh, int mm) : h(hh), m(mm) {}
    friend int minutesBetween(const Time& a, const Time& b);
    friend bool earlier(const Time& a, const Time& b);
};

int minutesBetween(const Time& a, const Time& b)
{
    int d = (a.h * 60 + a.m) - (b.h * 60 + b.m);
    return d < 0 ? -d : d;
}

bool earlier(const Time& a, const Time& b)
{
    return a.h * 60 + a.m < b.h * 60 + b.m;
}

int main()
{
    Time departure(9, 45), arrival(13, 10);
    std::cout << minutesBetween(departure, arrival) << ' '
              << std::boolalpha << earlier(arrival, departure) << '\n';

    Time t1(11, 59), t2(12, 1), t3(12, 0);
    std::cout << "same time: " << minutesBetween(t3, t3) << ' ' << earlier(t3, t3) << '\n';
    std::cout << "11:59 -> 12:01: " << minutesBetween(t1, t2) << " (hand: 2) " << earlier(t1, t2) << '\n';
    std::cout << "12:01 earlier than 11:59? " << earlier(t2, t1) << '\n';
}
