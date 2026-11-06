// Task 9: complete fare logic + table-driven tests.
#include <iomanip>
#include <iostream>

enum class Zone { Inner, Middle, Outer };
enum class Concession { None, Student, Senior };
constexpr int BASE_PAISE[] = {1000, 2000, 3000};
constexpr int PEAK_SURCHARGE_PERCENT = 20;
constexpr int CONCESSION_PERCENT_OFF = 50;      // assumption: students and seniors pay half
constexpr long long MIN_BALANCE_PAISE = 5000;

constexpr bool isPeak(int hour) { return (hour >= 8 && hour < 10) || (hour >= 17 && hour < 20); }

long long fare(Zone z, int hour, Concession c)
{
    long long f = BASE_PAISE[static_cast<int>(z)];
    if (isPeak(hour)) f += f * PEAK_SURCHARGE_PERCENT / 100;
    if (c != Concession::None) f -= f * CONCESSION_PERCENT_OFF / 100;
    return f;
}
bool canTravel(long long balance, long long f) { return balance - f >= MIN_BALANCE_PAISE; }

struct Test { const char* name; Zone z; int hour; Concession c; long long balance; long long expectFare; bool expectOk; };

int main()
{
    const Test tests[] = {
        {"Inner off-peak",          Zone::Inner,  12, Concession::None,    10000, 1000, true},
        {"Middle off-peak",         Zone::Middle, 12, Concession::None,    10000, 2000, true},
        {"Outer off-peak",          Zone::Outer,  12, Concession::None,    10000, 3000, true},
        {"Inner peak morning",      Zone::Inner,   9, Concession::None,    10000, 1200, true},
        {"Middle peak evening",     Zone::Middle, 18, Concession::None,    10000, 2400, true},
        {"Outer peak",              Zone::Outer,   8, Concession::None,    10000, 3600, true},
        {"Boundary 8:00 (peak)",    Zone::Inner,   8, Concession::None,    10000, 1200, true},
        {"Boundary 10:00 (off)",    Zone::Inner,  10, Concession::None,    10000, 1000, true},
        {"Boundary 17:00 (peak)",   Zone::Inner,  17, Concession::None,    10000, 1200, true},
        {"Boundary 20:00 (off)",    Zone::Inner,  20, Concession::None,    10000, 1000, true},
        {"Leaves exactly Rs 50",    Zone::Inner,  12, Concession::None,     6000, 1000, true},
        {"Leaves Rs 49.99",         Zone::Inner,  12, Concession::None,     5999, 1000, false},
        {"Student Outer peak",      Zone::Outer,   9, Concession::Student, 10000, 1800, true},
        {"Senior Middle off-peak",  Zone::Middle, 12, Concession::Senior,  10000, 1000, true},
    };
    int pass = 0, total = 0;
    std::cout << std::left << std::setw(26) << "Case" << std::setw(10) << "ExpFare" << std::setw(10)
              << "ActFare" << std::setw(8) << "ExpOK" << std::setw(8) << "ActOK" << "Result\n";
    for (const Test& t : tests) {
        long long f = fare(t.z, t.hour, t.c);
        bool ok = canTravel(t.balance, f);
        bool good = (f == t.expectFare && ok == t.expectOk);
        ++total; pass += good;
        std::cout << std::setw(26) << t.name << std::setw(10) << t.expectFare << std::setw(10) << f
                  << std::setw(8) << t.expectOk << std::setw(8) << ok << (good ? "PASS" : "FAIL") << '\n';
    }
    std::cout << pass << "/" << total << " tests passed\n";

    // Hand-calculated 5-journey total: 1000 + 2400 + 3000 + 1800 + 1000 = 9200 paise
    long long sum = fare(Zone::Inner, 12, Concession::None) + fare(Zone::Middle, 18, Concession::None)
                  + fare(Zone::Outer, 12, Concession::None) + fare(Zone::Outer, 9, Concession::Student)
                  + fare(Zone::Middle, 12, Concession::Senior);
    std::cout << "5-journey total: " << sum << " paise (hand calculation: 9200) "
              << (sum == 9200 ? "PASS" : "FAIL") << '\n';
}
