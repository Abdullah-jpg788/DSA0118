// Task 7: procedural version and OOP version of the same fare logic.
#include <iostream>

constexpr long long MIN_BALANCE_PAISE = 5000;

// ---------------- Procedural ----------------
long long balanceP = 10000;                     // anyone can modify this
bool canTravelP(long long fare) { return balanceP - fare >= MIN_BALANCE_PAISE; }
void deductP(long long fare) { balanceP -= fare; }   // does not check anything itself

// ---------------- Object-oriented ----------------
class SmartCard {
    long long balancePaise_;
public:
    explicit SmartCard(long long b) : balancePaise_{b >= 0 ? b : 0} {}
    bool canTravel(long long fare) const { return balancePaise_ - fare >= MIN_BALANCE_PAISE; }
    bool deduct(long long fare) {
        if (fare < 0 || !canTravel(fare)) return false;
        balancePaise_ -= fare;
        return true;
    }
    bool recharge(long long amount) {
        if (amount <= 0) return false;            // negative recharge rejected
        balancePaise_ += amount;
        return true;
    }
    long long balance() const { return balancePaise_; }
};

int main()
{
    std::cout << "== Procedural ==\n";
    deductP(6000);                               // forgot canTravelP -> balance below Rs 50
    std::cout << "balance after unchecked deduct: " << balanceP << " (rule broken: < 5000)\n";

    std::cout << "== OOP ==\n";
    SmartCard card{10000};
    std::cout << "deduct 6000: " << std::boolalpha << card.deduct(6000)
              << ", balance " << card.balance() << '\n';
    std::cout << "deduct 4000: " << card.deduct(4000) << ", balance " << card.balance() << '\n';
    std::cout << "recharge -500: " << card.recharge(-500) << '\n';
    std::cout << "recharge 2000: " << card.recharge(2000) << ", balance " << card.balance() << '\n';
    // card.balancePaise_ = -1;   // compile error: private member
}
