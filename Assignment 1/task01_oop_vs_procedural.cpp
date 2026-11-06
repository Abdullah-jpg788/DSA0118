// Task 1: objects in the metro fare problem, OOP style vs procedural style.
// Assumptions: concession = 50% for students/seniors; all money in integer paise.
#include <iostream>

constexpr int BASE_PAISE[] = {1000, 2000, 3000};
constexpr long long MIN_BALANCE_PAISE = 5000;

// ---------- Object-oriented version ----------
class FareTable {                       // abstraction: hides how fares are stored
public:
    long long base(int zone) const { return BASE_PAISE[zone]; }
};

class SmartCard {                       // encapsulation: balance is private
    long long balancePaise_;
public:
    explicit SmartCard(long long b) : balancePaise_{b} {}
    bool canTravel(long long fare) const { return balancePaise_ - fare >= MIN_BALANCE_PAISE; }
    bool deduct(long long fare) {       // the only way to reduce the balance
        if (!canTravel(fare)) return false;
        balancePaise_ -= fare;
        return true;
    }
    long long balance() const { return balancePaise_; }
};

class Journey {
    int zone_;
    bool peak_;
public:
    Journey(int z, bool p) : zone_{z}, peak_{p} {}
    long long fare(const FareTable& t) const {
        long long f = t.base(zone_);
        if (peak_) f += f * 20 / 100;
        return f;
    }
};

// ---------- Procedural version (globals + free functions) ----------
long long g_balance = 10000;
long long fareProc(int zone, bool peak)
{
    long long f = BASE_PAISE[zone];
    if (peak) f += f * 20 / 100;
    return f;
}

int main()
{
    FareTable table;
    SmartCard card{10000};
    Journey js[] = {{0, false}, {2, true}, {1, false}};
    std::cout << "--- OOP ---\n";
    for (const Journey& j : js) {
        long long f = j.fare(table);
        if (card.deduct(f)) std::cout << "fare " << f << " paise, balance " << card.balance() << '\n';
        else std::cout << "denied, balance " << card.balance() << '\n';
    }
    std::cout << "--- Procedural ---\n";
    int zones[] = {0, 2, 1};
    bool peaks[] = {false, true, false};
    for (int i = 0; i < 3; ++i) {
        long long f = fareProc(zones[i], peaks[i]);
        if (g_balance - f >= MIN_BALANCE_PAISE) {
            g_balance -= f;
            std::cout << "fare " << f << " paise, balance " << g_balance << '\n';
        } else std::cout << "denied, balance " << g_balance << '\n';
    }
    g_balance = -999;   // nothing stops this in the procedural version
    std::cout << "global balance can be corrupted: " << g_balance << '\n';
}
