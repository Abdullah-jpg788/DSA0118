// Task 12: redesign for Airport zone (Rs 60), 10% weekend discount (not combined with peak),
// and a monthly pass (unlimited journeys in two chosen zones).
#include <iomanip>
#include <iostream>

enum class Zone { Inner, Middle, Outer, Airport };
constexpr int ZONE_COUNT = 4;
constexpr long long BASE_PAISE[ZONE_COUNT] = {1000, 2000, 3000, 6000};  // one table indexed by zone
constexpr int PEAK_SURCHARGE_PERCENT = 20;
constexpr int WEEKEND_DISCOUNT_PERCENT = 10;
constexpr int CONCESSION_PERCENT_OFF = 50;
constexpr long long MIN_BALANCE_PAISE = 5000;

constexpr bool isPeak(int hour) { return (hour >= 8 && hour < 10) || (hour >= 17 && hour < 20); }

// Separate discount rule: weekend discount replaces the peak surcharge on weekends.
long long fare(Zone z, int hour, bool weekend, bool concession)
{
    long long f = BASE_PAISE[static_cast<int>(z)];
    if (weekend) f -= f * WEEKEND_DISCOUNT_PERCENT / 100;
    else if (isPeak(hour)) f += f * PEAK_SURCHARGE_PERCENT / 100;
    if (concession) f -= f * CONCESSION_PERCENT_OFF / 100;
    return f;
}

class MonthlyPass {
    Zone a_, b_;
public:
    MonthlyPass(Zone a, Zone b) : a_{a}, b_{b} {}
    bool covers(Zone z) const { return z == a_ || z == b_; }
};

class SmartCard {
    long long balance_;
    const MonthlyPass* pass_ = nullptr;
public:
    explicit SmartCard(long long b) : balance_{b} {}
    void attach(const MonthlyPass* p) { pass_ = p; }
    // Pass holders pay nothing in covered zones; otherwise the Rs 50 floor still applies.
    bool travel(Zone z, long long f) {
        if (pass_ && pass_->covers(z)) return true;
        if (balance_ - f < MIN_BALANCE_PAISE) return false;
        balance_ -= f;
        return true;
    }
    long long balance() const { return balance_; }
};

int main()
{
    struct Case { const char* name; Zone z; int hour; bool weekend; bool conc; long long expect; };
    const Case cases[] = {
        {"Airport weekday off-peak", Zone::Airport, 12, false, false, 6000},
        {"Airport weekday peak",     Zone::Airport,  9, false, false, 7200},
        {"Airport weekend peak hour",Zone::Airport,  9, true,  false, 5400},  // discount, no surcharge
        {"Outer weekend off-peak",   Zone::Outer,   12, true,  false, 2700},
        {"Inner weekday peak",       Zone::Inner,    8, false, false, 1200},
        {"Airport weekend student",  Zone::Airport, 12, true,  true,  2700},
    };
    int pass = 0;
    for (const Case& c : cases) {
        long long f = fare(c.z, c.hour, c.weekend, c.conc);
        bool ok = f == c.expect;
        pass += ok;
        std::cout << std::left << std::setw(28) << c.name << " expected " << std::setw(5) << c.expect
                  << " actual " << std::setw(5) << f << (ok ? " PASS" : " FAIL") << '\n';
    }
    std::cout << pass << "/6 fare tests passed\n";

    MonthlyPass mp{Zone::Inner, Zone::Middle};
    SmartCard card{10000};
    card.attach(&mp);
    std::cout << "pass, Inner:   " << card.travel(Zone::Inner, fare(Zone::Inner, 9, false, false))
              << " balance " << card.balance() << '\n';
    std::cout << "pass, Middle:  " << card.travel(Zone::Middle, fare(Zone::Middle, 9, false, false))
              << " balance " << card.balance() << '\n';
    std::cout << "pass, Airport: " << card.travel(Zone::Airport, fare(Zone::Airport, 12, false, false))
              << " balance " << card.balance() << " (pays 6000, leaves 4000 < 5000 floor -> denied)\n";
}
