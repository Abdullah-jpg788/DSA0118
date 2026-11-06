// Task 11: recommended design: constexpr defaults + FareTable class + SmartCard class,
// with an optional fare configuration file (alternative concept). Run: ./task11 [fares.cfg]
#include <fstream>
#include <iostream>

enum class Zone { Inner, Middle, Outer };
constexpr int ZONE_COUNT = 3;
constexpr int PEAK_SURCHARGE_PERCENT = 20;
constexpr long long MIN_BALANCE_PAISE = 5000;

class FareTable {
    long long base_[ZONE_COUNT] = {1000, 2000, 3000};   // compiled-in defaults
public:
    bool loadFromFile(const char* path) {               // alternative: read at start-up
        std::ifstream in{path};
        if (!in) return false;
        long long v[ZONE_COUNT];
        for (long long& x : v) if (!(in >> x) || x <= 0) return false;
        for (int i = 0; i < ZONE_COUNT; ++i) base_[i] = v[i];
        return true;
    }
    long long fare(Zone z, bool peak) const {
        long long f = base_[static_cast<int>(z)];
        return peak ? f + f * PEAK_SURCHARGE_PERCENT / 100 : f;
    }
};

class SmartCard {
    long long balance_;
public:
    explicit SmartCard(long long b) : balance_{b} {}
    bool canTravel(long long f) const { return balance_ - f >= MIN_BALANCE_PAISE; }
    bool deduct(long long f) { if (!canTravel(f)) return false; balance_ -= f; return true; }
    long long balance() const { return balance_; }
};

int main(int argc, char** argv)
{
    FareTable table;
    if (argc > 1) std::cout << (table.loadFromFile(argv[1]) ? "fares loaded from file\n"
                                                              : "config invalid, using defaults\n");
    SmartCard card{10000};
    struct Trip { Zone z; bool peak; };
    for (Trip t : {Trip{Zone::Inner, false}, Trip{Zone::Outer, true}, Trip{Zone::Middle, false}}) {
        long long f = table.fare(t.z, t.peak);
        std::cout << "fare " << f << " -> " << (card.deduct(f) ? "ok" : "denied")
                  << ", balance " << card.balance() << " paise\n";
    }
}
